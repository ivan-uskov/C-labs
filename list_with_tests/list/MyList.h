#pragma once

#include <memory>
#include <iterator>
#include <initializer_list>
#include <type_traits>

namespace
{
    template <typename T, typename = void>
    struct IsIterator
        : std::false_type
    {};

    template <typename T>
    struct IsIterator<T, std::void_t<typename std::iterator_traits<T>::iterator_category>>
        : std::true_type
    {};

    template <typename T1, typename T2>
    using IsSameWithoutConst = std::is_same<std::remove_const_t<T1>, std::remove_const_t<T2>>;
}

template <typename Value>
class CMyList
{
    typedef const Value ConstValue;
    typedef Value & ValueReference;
    typedef const Value & ValueConstReference;

    template <typename Value>
    struct ListNode;

    typedef ListNode<Value> Node;
    typedef std::shared_ptr<Node> NodePtr;

    template <typename Value>
    struct ListNode
    {
        std::unique_ptr<Value> value;
        NodePtr prev;
        NodePtr next;
    };

public:
    CMyList();
/*
    CMyList(size_t n, const Value & value);

    template<typename InputIterator, typename = std::enable_if_t<is_iterator<InputIterator>::value>>
    CMyList(InputIterator it, InputIterator last);

    CMyList(const CMyList & rhs);
    CMyList(CMyList && rhs);
    CMyList(std::initializer_list<Value> && list);
*/

    ~CMyList();

public:
    template <typename IteratorValue>
    class MyIterator : public std::iterator<std::bidirectional_iterator_tag, IteratorValue>
    {
        MyIterator(const CMyList<Value> * collection, const NodePtr & node);
    public:
        MyIterator(const MyIterator & rhs);

        template <typename AnotherIteratorValue, typename = std::enable_if_t<IsSameWithoutConst<IteratorValue, AnotherIteratorValue>::value>>
        bool operator == (const MyIterator<AnotherIteratorValue> & rhs) const noexcept;
        template <typename AnotherIteratorValue, typename = std::enable_if_t<IsSameWithoutConst<IteratorValue, AnotherIteratorValue>::value>>
        bool operator != (const MyIterator<AnotherIteratorValue> & rhs) const noexcept;

        operator MyIterator<const IteratorValue> ();
        IteratorValue & operator * () const;

        MyIterator & operator ++ ();
        MyIterator operator ++ (int);
        MyIterator & operator -- ();
        MyIterator operator -- (int);

    private:

        NodePtr m_node;
        const CMyList<Value> * m_collection = nullptr;

        friend class MyIterator<std::add_const_t<IteratorValue>>;
        friend class MyIterator<std::remove_const_t<IteratorValue>>;
        friend class CMyList<Value>;
    };

public:
    typedef MyIterator<Value>                    Iterator;
    typedef MyIterator<ConstValue>               ConstIterator;
    typedef std::reverse_iterator<Iterator>      ReverseIterator;
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    ReverseIterator rbegin();
    ReverseIterator rend();
    ConstReverseIterator rbegin() const;
    ConstReverseIterator rend() const;
    ConstReverseIterator crbegin() const;
    ConstReverseIterator crend() const;

public:
    size_t GetSize() const noexcept;
    bool IsEmpty() const noexcept;

    Iterator Erase(ConstIterator position);
    Iterator Erase(ConstIterator first, ConstIterator last);

    void Clear();

/*
    void Swap(CMyList & rhs) noexcept;

    void Resize(size_t n);
    void Resize(size_t n, const Value & value);
*/

public:

/*
    CMyList & operator = (const CMyList & rhs);
    CMyList & operator = (CMyList && rhs);
    CMyList & operator = (std::initializer_list<Value> && il);
*/

public:
    template <typename... Args>
    Iterator Emplace(const ConstIterator & position, Args&&... args);
/*
    template <class... Args>
    Iterator EmplaceBack(Args&&... args);

    template <class... Args>
    void EmplaceFront(Args&&... args);

    Iterator Insert(ConstIterator position, const Value & value);
    Iterator Insert(ConstIterator position, size_t n, const Value & value);
    template <typename InputIterator, typename = std::enable_if_t<is_iterator<InputIterator>::value>>
    Iterator Insert(ConstIterator position, InputIterator first, InputIterator last);
    Iterator Insert(ConstIterator position, Value && val);
    Iterator Insert(ConstIterator position, std::initializer_list<Value> list);

    template <typename InputIterator, typename = std::enable_if_t<is_iterator<InputIterator>::value>>
    void Assign(InputIterator first, InputIterator last);
    void Assign(size_t n, const Value & value);
    void Assign(std::initializer_list<Value> il);

    void PushBack(const Value & val);
    void PushBack(Value && val);

    void PushFront(const Value & val);
    void PushFront(Value && val);

    Value & Front();
    const Value & Front() const;

    Value & back();
    const Value & back() const;

    void PopBack();
    void PopFront();
*/
private:
    Iterator InsertAfter(const NodePtr & node, const NodePtr & nodeToBeInserted);
    template <typename... Args>
    NodePtr CreateNode(Args&&... args);

    template <typename T, typename = std::enable_if_t<IsIterator<T>::value>>
    T CreateIterator(const NodePtr & node);
    template <typename T, typename = std::enable_if_t<IsIterator<T>::value>>
    T CreateIterator(const NodePtr & node) const;

    void Initialize();

private:
    NodePtr m_preBeginNode = std::make_shared<Node>();
    NodePtr m_endNode = std::make_shared<Node>();
    size_t m_size = 0;
};

// ---------------------- Relational operators ----------------------

//TODO: test

template <typename Value>
bool operator == (const CMyList<Value> & lhs, const CMyList<Value> & rhs)
{
    return (lhs.GetSize() == rhs.GetSize()) && std::equal(lhs.begin, lhs.end(), rhs.begin(), rhs.end());
}

template <typename Value>
bool operator != (const CMyList<Value> & lhs, const CMyList<Value> & rhs)
{
    return !(lhs == rhs);
}

// ---------------------- Insertion ----------------------

template <typename Value>
template <typename... Args>
typename CMyList<Value>::Iterator CMyList<Value>::Emplace(const ConstIterator & position, Args&&... args)
{
    auto cendIt = cend();
    auto nodeBeforeNew = (position == cendIt ? cendIt.m_node->prev : position.m_node);
    return InsertAfter(nodeBeforeNew, CreateNode(std::forward<Args>(args)...));
}

// ---------------------- Erase ----------------------

template <typename Value>
typename CMyList<Value>::Iterator CMyList<Value>::Erase(ConstIterator position)
{
    if (position == cend())
    {
        throw std::logic_error("Erase end iterator");
    }

    auto node = position.m_node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    --m_size;

    return CreateIterator<Iterator>(node->next);
}

template <typename Value>
typename CMyList<Value>::Iterator CMyList<Value>::Erase(ConstIterator it, ConstIterator last)
{
    while (it != last)
    {
        Erase(it++);
    }
    auto lastNode = last.m_node;
    return CreateIterator<Iterator>(last.m_node);
}

template <typename Value>
void CMyList<Value>::Clear()
{
    Erase(cbegin(), cend());
}

// ---------------------- About size ----------------------

template <typename Value>
size_t CMyList<Value>::GetSize() const noexcept
{
    return m_size;
}

template <typename Value>
bool CMyList<Value>::IsEmpty() const noexcept
{
    return GetSize() == 0;
}

// ---------------------- Constructors ----------------------

template <typename Value>
CMyList<Value>::CMyList()
{
    Initialize();
}

// ---------------------- Destructor ----------------------

template <typename Value>
CMyList<Value>::~CMyList()
{
    Clear();
    m_preBeginNode->next.reset();
    m_endNode->prev.reset();
}

// ---------------------- Iterator constructor ----------------------

template <typename Value>
template <typename IteratorValue>
CMyList<Value>::MyIterator<IteratorValue>::MyIterator(const CMyList<Value> * collection, const NodePtr & node)
    : m_collection(collection)
    , m_node(node)
{}

template <typename Value>
template <typename IteratorValue>
CMyList<Value>::MyIterator<IteratorValue>::MyIterator(const MyIterator & rhs)
    : MyIterator(rhs.m_collection, rhs.m_node)
{}

// ---------------------- Iterator operators ----------------------

template <typename Value>
template <typename IteratorValue>
template <typename AnotherIteratorValue, typename>
bool CMyList<Value>::MyIterator<IteratorValue>::operator == (const MyIterator<AnotherIteratorValue> & rhs) const noexcept
{
    return (m_collection == rhs.m_collection) && (m_node.get() == rhs.m_node.get());
}

template <typename Value>
template <typename IteratorValue>
template <typename AnotherIteratorValue, typename>
bool CMyList<Value>::MyIterator<IteratorValue>::operator != (const MyIterator<AnotherIteratorValue> & rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename Value>
template <typename IteratorValue>
CMyList<Value>::MyIterator<IteratorValue>::operator MyIterator<const IteratorValue> ()
{
    return MyIterator<const IteratorValue>(m_collection, m_node);
}

template <typename Value>
template <typename IteratorValue>
IteratorValue & CMyList<Value>::MyIterator<IteratorValue>::operator * () const
{
    return *(m_node->value);
}

template <typename Value>
template <typename IteratorValue>
typename CMyList<Value>::MyIterator<IteratorValue> & CMyList<Value>::MyIterator<IteratorValue>::operator ++ ()
{
    if (*this == m_collection->end())
    {
        throw std::logic_error("Increment end iterator");
    }

    m_node = m_node->next;

    return *this;
}

template <typename Value>
template <typename IteratorValue>
typename CMyList<Value>::MyIterator<IteratorValue> CMyList<Value>::MyIterator<IteratorValue>::operator ++ (int)
{
    MyIterator<IteratorValue> copy(*this);
    ++(*this);
    return copy;
}

template <typename Value>
template <typename IteratorValue>
typename CMyList<Value>::MyIterator<IteratorValue> & CMyList<Value>::MyIterator<IteratorValue>::operator -- ()
{
    if (*this == m_collection->begin())
    {
        throw std::logic_error("Decrement begin iterator");
    }

    m_node = m_node->prev;

    return *this;
}

template <typename Value>
template <typename IteratorValue>
typename CMyList<Value>::MyIterator<IteratorValue> CMyList<Value>::MyIterator<IteratorValue>::operator -- (int)
{
    MyIterator<IteratorValue> copy(*this);
    --(*this);
    return copy;
}

// --------------- iterator_getters --------------

template <typename Value>
typename CMyList<Value>::Iterator CMyList<Value>::begin()
{
    return CreateIterator<Iterator>(m_preBeginNode->next);
}

template <typename Value>
typename CMyList<Value>::Iterator CMyList<Value>::end()
{
    return CreateIterator<Iterator>(m_endNode);
}

template <typename Value>
typename CMyList<Value>::ConstIterator CMyList<Value>::begin() const
{
    return CreateIterator<ConstIterator>(m_preBeginNode->next);
}

template <typename Value>
typename CMyList<Value>::ConstIterator CMyList<Value>::end() const
{
    return CreateIterator<ConstIterator>(m_endNode);
}

template <typename Value>
typename CMyList<Value>::ConstIterator CMyList<Value>::cbegin() const
{
    return begin();
}

template <typename Value>
typename CMyList<Value>::ConstIterator CMyList<Value>::cend() const
{
    return end();
}

// --------------- reverse_iterators_getters --------------

template <typename Value>
typename CMyList<Value>::ReverseIterator CMyList<Value>::rbegin()
{
    return ReverseIterator(end());
}

template <typename Value>
typename CMyList<Value>::ReverseIterator CMyList<Value>::rend()
{
    return ReverseIterator(begin());
}

template <typename Value>
typename CMyList<Value>::ConstReverseIterator CMyList<Value>::rbegin() const
{
    return ConstReverseIterator(end());
}

template <typename Value>
typename CMyList<Value>::ConstReverseIterator CMyList<Value>::rend() const
{
    return ConstReverseIterator(begin());
}

template <typename Value>
typename CMyList<Value>::ConstReverseIterator CMyList<Value>::crbegin() const
{
    return rbegin();
}

template <typename Value>
typename CMyList<Value>::ConstReverseIterator CMyList<Value>::crend() const
{
    return rend();
}

// ---------------------- Helpers ----------------------

template <typename Value>
typename CMyList<Value>::Iterator CMyList<Value>::InsertAfter(const NodePtr & node, const NodePtr & nodeToBeInserted)
{
    nodeToBeInserted->next = node->next;
    nodeToBeInserted->prev = node;
    node->next->prev = nodeToBeInserted;
    node->next = nodeToBeInserted;

    ++m_size;

    return CreateIterator<Iterator>(nodeToBeInserted);
}

template <typename Value>
template <typename... Args>
typename CMyList<Value>::NodePtr CMyList<Value>::CreateNode(Args&&... args)
{
    auto node = std::make_shared<Node>();
    node->value = std::make_unique<Value>(std::forward<Args>(args)...);

    return node;
}

template <typename Value>
void CMyList<Value>::Initialize()
{
    m_preBeginNode->next = m_endNode;
    m_endNode->prev = m_preBeginNode;
}

template <typename Value>
template <typename T, typename>
T CMyList<Value>::CreateIterator(const NodePtr & node)
{
    return T(this, node);
}

template <typename Value>
template <typename T, typename>
T CMyList<Value>::CreateIterator(const NodePtr & node) const
{
    return T(this, node);
}