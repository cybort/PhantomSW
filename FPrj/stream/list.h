
#ifndef _LIST_H_
#define _LIST_H_

template <typename T> class Node
{
public:
    Node<T> * next;
    Node<T> * prev;
    T data;
};

template <typename T> class List
{
public:
    List();
    List(const List & ln);
    ~List();
    void add(T e);             //添加节点
    void ascSort();            //升序排序
    void remove(T index);      //移除某个结点
    Node<T> * find(int index); //查找结点
    bool isEmpty();            //判断是否为空
    int size();                //链表长度
    void show();               //显示链表
    void resShow();            //链表反向显示
    void removeAll();          //删除全部结点
private:
    Node<T> * head;
    Node<T> * tail;
    int length;
};

//默认构造函数
template <class T> List<T>::List()
{
    head = new Node<T>;
    tail = new Node<T>;
    head->next = tail;
    head->prev = NULL;
    tail->next = NULL;
    tail->prev = head;
    length = 0;
}
//拷贝构造函数
template <typename T> List<T>::List(const List & ln)
{
    head = new Node<T>;
    head->prev = NULL;
    tail = new Node<T>;
    head->next = tail;
    tail->prev = head;
    length = 0;
    Node<T> * temp = ln.head;
    while (temp->next != ln.tail)
    {
        temp = temp->next;
        tail->data = temp->data;
        Node<T> * p = new Node<T>;
        p->prev = tail;
        tail->next = p;
        tail = p;
        length++;
    }
    tail->next = NULL;
}
//向链表添加数据
template <typename T> void List<T>::add(T e)
{
    Node<T> * tail_pre = this->tail;
    tail->data = e;
    tail->next = new Node<T>;
    //    Node<T> * p = tail;
    tail = tail->next;
    tail->prev = tail_pre;
    tail->next = NULL;
    length++;
}
//查找结点
template <typename T> Node<T> * List<T>::find(int index)
{
    if (length == 0)
    {
        std::cout << "List is empty";
        return NULL;
    }
    if (index >= length)
    {
        std::cout << "Out of bounds";
        return NULL;
    }
    int x = 0;
    Node<T> * p;
    if (index < length / 2)
    {
        p = head->next;
        while (p->next != NULL && x++ != index)
        {
            p = p->next;
        }
    }
    else
    {
        p = tail->prev;
        while (p->prev != NULL && length != (index + x++ + 1))
        {
            p = p->prev;
        }
    }
    return p;
}
//删除结点
template <typename T> void List<T>::remove(T index)
{
    if (length == 0)
    {
        std::cout << "List is empty";
        return;
    }
    Node<T> * p = head;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->data == index)
        {
            Node<T> * temp = p->prev;
            temp->next = p->next;
            p->next->prev = temp;
            delete p;
            length--;
            return;
        }
    }
}
//删除所有结点
template <typename T> void List<T>::removeAll()
{
    if (length == 0)
    {
        return;
    }
    Node<T> * p = head->next;
    while (p != tail)
    {
        Node<T> * temp = p;
        p = p->next;
        delete temp;
    }
    head->next = tail;
    tail->prev = head;
    length = 0;
}
//升序排序
template <typename T> void List<T>::ascSort()
{
    if (length <= 1)
        return;
    Node<T> * p = head->next;
    for (int i = 0; i < length - 1; i++)
    {
        Node<T> * q = p->next;
        for (int j = i + 1; j < length; j++)
        {
            if (p->data > q->data)
            {
                T temp = q->data;
                q->data = p->data;
                p->data = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
}
//判断是否为空
template <typename T> bool List<T>::isEmpty()
{
    if (length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//链表长度
template <typename T> int List<T>::size() { return length; }
//输出链表
template <typename T> void List<T>::show()
{
    if (length == 0)
    {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node<T> * p = head->next;
    while (p != tail)
    {
        //       std::cout << p->data.pktdata.get_bytes() << " ";
        p = p->next;
    }
    std::cout << std::endl;
}
//反向输出链表
template <typename T> void List<T>::resShow()
{
    if (length == 0)
        return;
    Node<T> * p = tail->prev;
    while (p != head)
    {
        //        std::cout << p->data << " ";
        p = p->prev;
    }
    std::cout << std::endl;
}
//析构函数,2 list 
template <typename T> List<T>::~List()
{
    if (length == 0)
    {
        delete head;
        delete tail;
        head = NULL;
        tail = NULL;
        return;
    }

    while (head->next != NULL)
    {
        Node<T> * temp = head;
        head = head->next;
        delete temp;
    }
    delete head;
    head = NULL;

}
#endif