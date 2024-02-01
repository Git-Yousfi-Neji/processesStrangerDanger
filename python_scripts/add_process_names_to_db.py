import sqlite3
import xml.etree.ElementTree as ET

def read_xml_to_list(xml_file):
    process_names = []

    tree = ET.parse(xml_file)
    root = tree.getroot()

    for username_element in root.iter('systemUsernames'):
        process_names.append(username_element.text)

    return process_names

def create_database():
    conn = sqlite3.connect('data/systemUsernames.db')
    cursor = conn.cursor()

    # Create a table to store process names
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS process_names (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE
        )
    ''')

    conn.commit()
    return conn, cursor

def insert_process_names(cursor, process_names):
    for name in process_names:
        try:
            cursor.execute('INSERT INTO process_names (name) VALUES (?)', (name,))
        except sqlite3.IntegrityError:
            # Ignore duplicates
            pass

def main():
    xml_file = 'data/systemUsernames.xml'
    process_names = read_xml_to_list(xml_file)

    conn, cursor = create_database()

    insert_process_names(cursor, process_names)

    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()
