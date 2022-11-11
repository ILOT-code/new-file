import time
import struct
from matplotlib import pyplot as plt
import numpy as np
from sklearn import svm


def load_data(kind):
    labels_path = ('%s-labels.idx1-ubyte' % kind)
    images_path = ('%s-images.idx3-ubyte' % kind)
    with open(labels_path, 'rb') as lbpath:
        magic, n = struct.unpack('>II', lbpath.read(8))
        labels = np.fromfile(lbpath, dtype=np.uint8)
    with open(images_path, 'rb') as imgpath:
        magic, num, rows, cols = struct.unpack(">IIII", imgpath.read(16))
        images = np.fromfile(imgpath, dtype=np.uint8).reshape(num, rows * cols)
    return images, labels


def train(X_train, Y_train, train_num):
    x_train = X_train[0:train_num]
    y_train = Y_train[0:train_num]

    time_start = time.time()
    model_svc = svm.SVC(kernel='rbf', gamma='scale')
    model_svc.fit(x_train, y_train)
    time_end = time.time()
    print('train: time cost', time_end - time_start, 's')
    return model_svc


def test(X_test, Y_test, test_num, model_svc):
    x_test = X_test[0:test_num]
    y_test = Y_test[0:test_num]
    time_start = time.time()
    score = model_svc.score(x_test, y_test)
    print('score:%lf' % score)
    time_end = time.time()
    print('test: time cost', time_end - time_start, 's')
    return score


def pred(model_svc, pred_num, X_test):
    y_pred = model_svc.predict(X_test[0:pred_num])
    for i in range(pred_num):
        x_show = X_test[i].reshape(28, 28)
        plt.subplot(1, pred_num, i + 1)
        plt.imshow(x_show)
        plt.title(str(y_pred[i]))
        plt.axis('off')
    plt.show()


if __name__ == '__main__':
    X_train, Y_train = load_data('train')
    X_test, Y_test = load_data('t10k')
    model = train(X_train, Y_train, 60000)
    test(X_test, Y_test, 10000, model)
    pred(model, 20, X_test)
