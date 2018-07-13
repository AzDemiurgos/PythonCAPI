
import Accelerate_Py


def main():
    llist =[[1,23,4,523],[1,23,4,523],[1,23,4,523]]
    llist2 = [678,252,252,2532]
    from Accelerate_Py import Accelerate_Py_Func
    temp = Accelerate_Py_Func(llist, llist2, 5)
    #from module1 import example
    #temp  = example(llist, llist2, 6)
    print(temp)
    temp = "a"
    
    print(temp)

if __name__ == "__main__":
    main()
    
