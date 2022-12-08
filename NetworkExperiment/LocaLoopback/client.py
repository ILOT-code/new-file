import socket

# 创建套接字
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # SOCK_STREAM=》TCP协议

# 连接服务器
client.connect(("127.0.0.1", 8080))

# 与服务器进行通信循环
while True:
    msg = input(">>: ").strip()
    if(msg == '！'):
        break
    client.send(msg.encode('utf-8'))
    data = client.recv(1024)
    print("服务端返回的数据：", data.decode('utf-8'))

# 关闭
client.close()
