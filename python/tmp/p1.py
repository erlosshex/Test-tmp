# -*-coding:utf-8-*-

def divide_and_modular(my_str,base=2):
    if len(my_str)==0:
        return [],None
    d=[]
    m=0
    for i in my_str:
        tmp=m*10+ord(i)-ord('0')
        d.append(tmp/base)
        m=tmp%base
    return d,m

if __name__=='__main__':
    n_str=raw_input('please input a number:')

    d,m=divide_and_modular(n_str)

    print n_str,' --> ',reduce(lambda acc,x: acc*10+x,d),' ',m
