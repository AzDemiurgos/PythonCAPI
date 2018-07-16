
import Accelerate_Py
import numpy as np


def main():

    data = np.load("E:\Azat\C_AMP\ss_logs.npy")
   # //data.
    listlist = []
    lambdas = []
    for i in range(1,data.shape[1]):
        listlist.append([])
        lambdas.append(0.1)

    for i in range(1,data.shape[1]):
        for j in range(0,data.shape[0]):
            listlist[i-1].append(data[j][i])

    
    from Accelerate_Py import Accelerate_Py_Func
    temp = Accelerate_Py_Func(listlist, lambdas, 100)
    #from module1 import example
    #temp  = example(llist, llist2, 6)
    import matplotlib.pyplot as plt
    plt.figure()
    plt.plot(data[:,11], color='r')
    plt.plot(temp[10], color='b')
    plt.grid(True)
    plt.show()
    
    #print(temp)
    temp = "a"
    
    print(temp)

if __name__ == "__main__":
    main()
    
