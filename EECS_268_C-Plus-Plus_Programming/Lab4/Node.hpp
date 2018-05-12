using namespace std;
template <class T> Node<T>::Node()
{
	m_value=0;
	m_next=nullptr;
}
template <class T> void Node<T>::setValue(T val)
	{
		m_value=val;
	}
template <class T> void Node<T>::setNext(Node<T>* prev)
	{
		m_next=prev;
	}
template <class T> T Node<T>::getValue() const
	{
		return m_value;
	}
template <class T> Node<T>* Node<T>::getNext() const
	{
		return m_next;
	}
