if __name__ == '__main__':

    X_train, Y_train = load_data('train')
    X_test, Y_test = load_data('t10k')
    model_svc = svm.SVC(kernel='rbf', gamma='scale')
    x = []
    y = []
    for i in range(30):
        x_train = X_train[0:(i + 1) * 2000]
        y_train = Y_train[0:(i + 1) * 2000]
        model_svc.fit(x_train, y_train)
        x.append((i + 1) * 2000)
        y.append(test(X_test, Y_test, 2000, model_svc))
    print(y)
    fig = plt.figure()
    ax1 = fig.add_subplot()
    ax1.plot(x, y)
    plt.show()
