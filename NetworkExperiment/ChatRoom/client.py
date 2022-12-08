import socket
import threading
host = '10.15.233.89'  # 服务器IP地址
port = 6789  # 服务器端口号
nickname = input("输入你的昵称（这是你在本聊天室的唯一标识）: ")  # 输入在聊天室的昵称
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建socket
client.connect((host, port))  # 连接到服务器
# 接受服务器消息


def receive():
    while True:
        try:
            message = client.recv(1024).decode('utf-8')
            if message == 'NICKNAME':  # 这个特殊信息意味着填入昵称
                client.send(nickname.encode('utf-8'))
            else:
                print(message)
        except:  # 退出
            print("An error occured!")
            client.close()
            break
# 发送聊天消息


def write():
    while True:
        message = '{}: {}'.format(nickname, input(''))
        client.send(message.encode('utf-8'))


# 启动接受信息与发送信息两个进程
receive_thread = threading.Thread(target=receive)
receive_thread.start()
write_thread = threading.Thread(target=write)
write_thread.start()
