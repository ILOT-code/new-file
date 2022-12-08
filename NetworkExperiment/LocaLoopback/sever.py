import socket

# 创建socket
sever = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # SOCK_STREAM=》TCP协议

# 绑定地址与端口
sever.bind(("127.0.0.1", 8080))  # 本地回环

# 开始监听
sever.listen(100)
print('服务器开始监听' + ' ''服务器IP与端口： %s:%s' % ("127.0.0.1", 8080))

# 当有连接接入时
while True:
    client, client_addr = sever.accept()
    print(str(client_addr) + '连接到了服务器')

    # 与当前客户端进行消息通信循环
    while True:
        data = client.recv(1024)  # 最大接收的字节个数
        if(data == '！'):
            break
        print("收到的客户端数据：", data.decode('utf-8'))
        client.send(data)

    # 当前客户端断开连接
    print(str(client_addr) + '断开连接')
    client.close()

# 关闭
sever.close()
