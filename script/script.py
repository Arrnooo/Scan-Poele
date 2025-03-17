import paho.mqtt.client as mqtt
import pandas as pd
import curses

# Initialisation du tableau des valeurs
data = pd.DataFrame(columns=["Topic", "Valeur"])
reading = True  # Variable pour gérer la lecture des messages

def on_connect(client, userdata, flags, rc):
    print("Connecté avec le code de résultat:", rc)
    client.subscribe("PoeleScan/#")  # S'abonner à tous les topics

def on_message(client, userdata, msg):
    global data, reading
    if not reading:
        return
    
    topic = msg.topic
    valeur = msg.payload.decode()
    
    # Vérifier si le topic existe déjà dans le tableau
    if topic in data["Topic"].values:
        data.loc[data["Topic"] == topic, "Valeur"] = valeur
    else:
        new_row = pd.DataFrame([[topic, valeur]], columns=["Topic", "Valeur"])
        data = pd.concat([data, new_row], ignore_index=True)

def display_table(stdscr):
    global data, reading
    client.loop_start()
    curses.curs_set(0)  # Cacher le curseur
    
    while True:
        stdscr.clear()
        stdscr.addstr(0, 0, "Topic", curses.A_BOLD)
        stdscr.addstr(0, 30, "Valeur", curses.A_BOLD)
        stdscr.addstr(0, 60, "[Espace] Pause/Reprise | [R] Réinitialiser | [Q] Quitter", curses.A_BOLD)
        
        for idx, row in enumerate(data.itertuples(), start=1):
            stdscr.addstr(idx, 0, row.Topic)
            stdscr.addstr(idx, 30, str(row.Valeur))
        
        stdscr.refresh()
        key = stdscr.getch()
        
        if key == ord(' '):  # Pause/Reprise
            reading = not reading
        elif key == ord('r'):  # Réinitialiser les valeurs
            data = pd.DataFrame(columns=["Topic", "Valeur"])
        elif key == ord('q'):  # Quitter
            break
        
        curses.napms(500)  # Rafraîchir toutes les 500ms

# Configuration du client MQTT
broker_address = "192.168.0.42"  # Remplacez par l'adresse de votre broker
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(broker_address, 1883, 60)

# Démarrer l'interface curses
curses.wrapper(display_table)
