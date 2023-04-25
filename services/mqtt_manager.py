import subprocess

def main():
    username = 'admin'
    topic = 'gato_tempura'

    subprocess.run(['gcc', 'mqtt.c', '-o', 'mqtt'])
    subprocess.call([f'./mqtt {username} {topic}'])


if __name__ == '__main__':
    main()
