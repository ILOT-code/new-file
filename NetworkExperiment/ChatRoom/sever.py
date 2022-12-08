import socket
import threading
host = '10.15.233.89'  # 服务器IP地址
port = 6789  # 服务器端口
Max_cilent = 10  # 聊天室最大容量
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建TCP类型socket
server.bind((host, port))  # 绑定监听端口
server.listen(Max_cilent)  # 设定最大监听数
clients = []  # 维护当前在线的客户端
nicknames = []  # 维护当前在线的昵称号
cnt = 0  # 当前在线人数


def broadcast(message):  # 广播
    for client in clients:
        client.send(message)


def add(nickname, client):  # 加入一个用户，维护客户信息
    flag = 1  # 这个标志表示是否是已经在线的用户
    for nickn in nicknames:
        if nickname == nickn:
            flag = 0  # 已在线用户的重复登录
            break
    if flag:
        clients.append(client)  # 维护相应信息
        nicknames.append(nickname)
    global cnt
    cnt = cnt + flag  # 更新在线人数
    print("{}加入了聊天室.现在在线人数是：{}".format(nickname, cnt))
    broadcast("{}加入了聊天室!现在在线人数是：{}.".format(nickname, cnt).encode('utf-8'))

# 有人离开，更新信息


def delete(client):
    index = clients.index(client)
    clients.remove(client)
    client.close()
    nickname = nicknames[index]
    nicknames.remove(nickname)
    global cnt
    cnt = cnt - 1
    print('{} 离开了!现在在线人数是：{}'.format(nickname, cnt))
    broadcast('{} 离开了!现在在线人数是：{}'.format(nickname, cnt).encode('utf-8'))  # 广播更新的信息

# 建立对应一个客户端连接的进程


def handle(client):
    while True:
        try:
            message = client.recv(1024)
            broadcast(message)  # 广播该消息
        except:  # 删除该客户
            delete(client)
            break


def receive():
    print('服务器已启动，监听中...')
    while True:
        client, address = server.accept()
        print("{}正在连接".format(str(address)))
        client.send('NICKNAME'.encode('utf-8'))  # 发送命名请求
        nickname = client.recv(1024).decode('utf-8')
        add(nickname, client)
        client.send('你已成功连接到服务器'.encode('utf-8'))
        thread = threading.Thread(target=handle, args=(client,))
        thread.start()  # 与客户端建立会话


receive()
