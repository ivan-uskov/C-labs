#pragma once

#include <memory>
#include <iterator>
#include <initializer_list>
#include <type_traits>

namespace
{
    template <typename T, typename = void>
    struct is_iterator
        : std::false_type
    {};

    template <typename T>
    struct is_iterator<T, std::void_t<typename std::iterator_traits<T>::iterator_category>>
        : std::true_type
    {};
}

template <typename Value>
class List : public std::enable_shared_from_this<List<Value>>
{
    template <typename Value>
    struct ListNode;

    typedef Value & reference;
    typedef const Value & const_reference;

    typedef ListNode<Value> Node;
    typedef std::shared_ptr<Node> NodePtr;

    template <typename Value>
    struct ListNode
    {
        template <typename... Args>
        ListNode(Args&&... args)
            : value(std::forward<Args>(args)...)
        {}

        Value value;
        NodePtr prev;
        NodePtr next;
    };

public:
    List() = default;

    template<typename InputIterator, typename = std::enable_if_t<is_iterator<InputIterator>::value>>
    List(InputIterator it, InputIterator last);

    List(std::initializer_list<Value> && list);
    ~List();

public:
    template <typename Value>
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, Value>
    {
    public:
        Iterator() = default;

        explicit Iterator(const std::shared_ptr<List<Value>> & collection, const NodePtr & node, const NodePtr & prevNode = nullptr);

        operator bool() const;

        Iterator & operator = (const Iterator<Value> & it);
        Iterator & operator ++ ();
        Iterator operator ++ (int);
        Iterator & operator -- ();
        Iterator operator -- (int);
        bool operator == (const Iterator & rhs);
        bool operator != (const Iterator & rhs);

        reference operator * () const
        {
            if (!mCurrentNode)
            {
                throw std::logic_error("null pointer dereference");
            }

            return mCurrentNode->value;
        }

        pointer operator -> () const
        {
            return **mCurrentNode;
        }

    private:
        friend class List<std::remove_const_t<Value>>;
        NodePtr mPrevNode;
        NodePtr mCurrentNode;
        std::shared_ptr<List<Value>> mCollection;
    };

public:
    typedef Iterator<Value>                       iterator;
    typedef Iterator<const Value>                 const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

public:
    bool operator == (const List<Value> & rhs);

public:
    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args);

    template <class... Args>
    iterator emplace_back(Args&&... args);

    template <class... Args>
    void emplace_front(Args&&... args);

    iterator insert(const_iterator position, const Value & value);
    iterator insert(const_iterator position, size_t n, const Value & value);
    template <typename InputIterator, typename = std::enable_if_t<is_iterator<InputIterator>::value>>
    iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, Value && val);
    iterator insert(const_iterator position, std::initializer_list<Value> list);

    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    void push_back(const Value & val);
    void push_back(Value && val);

    void push_front(const Value & val);
    void push_front(Value && val);

    void pop_back();
    void pop_front();

    void swap(List & x);

private:
    template <typename T, typename = std::enable_if_t<is_iterator<T>::value>>
    T createIterator(const NodePtr & node, const NodePtr & prevNode = nullptr);
    template <typename T, typename = std::enable_if_t<is_iterator<T>::value>>
    T createIterator(const NodePtr & node, const NodePtr & prevNode = nullptr) const;

    template <typename T, typename = std::enable_if_t<is_iterator<T>::value>>
    bool isIteratorValid(const T & it);

private:
    void verifyNotEmpty() const;
    iterator insertToEmpty(const NodePtr & nodeToBeInserted);
    iterator insertAfter(const NodePtr & node, const NodePtr & nodeToBeInserted);

private:
    NodePtr mFirstNode;
    NodePtr mLastNode;
    size_t mSize = 0;
};

// --------------- iterator --------------

template <typename Value>
template <typename ItValue>
List<Value>::Iterator<ItValue>::Iterator(const std::shared_ptr<List<ItValue>> & collection, const NodePtr & node, const NodePtr & prevNode = nullptr)
    : mCurrentNode(node)
    , mPrevNode(prevNode)
    , mCollection(collection)
{}

template <typename Value>
template <typename ItValue>
List<Value>::Iterator<ItValue>::operator bool() const
{
    return static_cast<bool>(mCurrentNode);
}

template <typename Value>
template <typename ItValue>
typename List<Value>::Iterator<ItValue> & List<Value>::Iterator<ItValue>::operator = (const Iterator<ItValue> & it)
{
    mCurrentNode = it.mCurrentNode;
    mPrevNode = it.mPrevNode;
    return *this;
}

template <typename Value>
template <typename ItValue>
typename List<Value>::Iterator<ItValue> & List<Value>::Iterator<ItValue>::operator ++ ()
{
    if (mCurrentNode)
    {
        mPrevNode = mCurrentNode;
        mCurrentNode = mCurrentNode->next;
    }

    return *this;
}

template <typename Value>
template <typename ItValue>
typename List<Value>::Iterator<ItValue> List<Value>::Iterator<ItValue>::operator ++ (int)
{
    Iterator<ItValue> copy(*this);
    ++(*this);
    return copy;
}

template <typename Value>
template <typename ItValue>
typename List<Value>::Iterator<ItValue> & List<Value>::Iterator<ItValue>::operator -- ()
{
    if (mCurrentNode)
    {
        mCurrentNode = mCurrentNode->prev;
        mPrevNode = mCurrentNode;
    }
    else if (mPrevNode)
    {
        mCurrentNode = mPrevNode;
        mPrevNode = nullptr;
    }

    return *this;
}

template <typename Value>
template <typename ItValue>
typename List<Value>::Iterator<ItValue> List<Value>::Iterator<ItValue>::operator -- (int)
{
    Iterator<ItValue> copy(*this);
    --(*this);
    return copy;
}

template <typename Value>
template <typename ItValue>
bool List<Value>::Iterator<ItValue>::operator == (const Iterator & rhs)
{
    return mCurrentNode == rhs.mCurrentNode;
}

template <typename Value>
template <typename ItValue>
bool List<Value>::Iterator<ItValue>::operator != (const Iterator & rhs)
{
    return !(*this == rhs);
}

// --------------- operators --------------

template <typename Value>
bool List<Value>::operator == (const List<Value> & rhs)
{
    return (size() == rhs.size()) && std::equal(begin(), end(), rhs.begin(), rhs.end());
}

// --------------- iterator_getters --------------

template <typename Value>
typename List<Value>::iterator List<Value>::begin()
{
    return createIterator<iterator>(mFirstNode);
}

template <typename Value>
typename List<Value>::iterator List<Value>::end()
{
    return createIterator<iterator>(nullptr, mLastNode);
}

template <typename Value>
typename List<Value>::const_iterator List<Value>::begin() const
{
    return createIterator<const_iterator>(mFirstNode);
}

template <typename Value>
typename List<Value>::const_iterator List<Value>::end() const
{
    return createIterator<const_iterator>(nullptr, mLastNode);
}

template <typename Value>
typename List<Value>::const_iterator List<Value>::cbegin() const
{
    return begin();
}

template <typename Value>
typename List<Value>::const_iterator List<Value>::cend() const
{
    return end();
}

// --------------- reverse_iterators_getters --------------

template <typename Value>
typename List<Value>::reverse_iterator List<Value>::rbegin()
{
    return reverse_iterator(end());
}

template <typename Value>
typename List<Value>::reverse_iterator List<Value>::rend()
{
    return reverse_iterator(begin());
}

template <typename Value>
typename List<Value>::const_reverse_iterator List<Value>::rbegin() const
{
    return const_reverse_iterator(end());
}

template <typename Value>
typename List<Value>::const_reverse_iterator List<Value>::rend() const
{
    return const_reverse_iterator(begin());
}

template <typename Value>
typename List<Value>::const_reverse_iterator List<Value>::crbegin() const
{
    return rbegin();
}

template <typename Value>
typename List<Value>::const_reverse_iterator List<Value>::crend() const
{
    return rend();
}

// --------------- constructors --------------

template <typename Value>
template<typename InputIterator, typename>
List<Value>::List(InputIterator first, InputIterator last)
{
    insert(cend(), first, last);
}

template <typename Value>
List<Value>::List(std::initializer_list<Value> && list)
    : List(list.begin(), list.end())
{}

// --------------- destructors --------------

template <typename Value>
List<Value>::~List()
{
    clear();
}

// --------------- member functions --------------

template <typename Value>
template <class... Args>
typename List<Value>::iterator List<Value>::emplace(const_iterator position, Args&&... args)
{
    auto newNode = std::make_shared<Node>(std::forward<Args>(args)...);
    if (empty())
    {
        return insertToEmpty(newNode);
    }
    else
    {
        auto insertionPos = position ? position.mCurrentNode : mLastNode;
        return insertAfter(insertionPos, newNode);
    }
}

template <typename Value>
template <class... Args>
typename List<Value>::iterator List<Value>::emplace_back(Args&&... args)
{
    emplace(cend, std::forward<Args>(args)...);
}

template <typename Value>
template <class... Args>
void List<Value>::emplace_front(Args&&... args)
{
    auto newNode = std::make_shared<Node>(std::forward<Args>(args)...);
    if (empty())
    {
        insertToEmpty(newNode);
    }
    else
    {
        newNode->next = mFirstNode;
        mFirstNode->prev = newNode;
        mFirstNode = newNode;
        ++mSize;
    }
}

template <typename Value>
typename List<Value>::iterator List<Value>::insert(const_iterator position, const Value & value)
{
    return emplace(position, value);
}

template <typename Value>
typename List<Value>::iterator List<Value>::insert(const_iterator position, size_t n, const Value & value)
{
    auto lastInserted = end();
    while (n-- > 0)
    {
        lastInserted = emplace(position, value);
    }

    return lastInserted;
}

template <typename Value>
template <typename InputIterator, typename>
typename List<Value>::iterator List<Value>::insert(const_iterator position, InputIterator first, InputIterator last)
{
    auto insertionPos = position ? position : cend();
    for (auto it = first; it != last; ++it)
    {
        insertionPos = createIterator<const_iterator>(emplace(insertionPos, *it).mCurrentNode);
    }

    return createIterator<iterator>(insertionPos.mCurrentNode);
}

template <typename Value>
typename List<Value>::iterator List<Value>::insert(const_iterator position, Value && val)
{
    return emplace(position, std::move(val));
}

template <typename Value>
typename List<Value>::iterator List<Value>::insert(const_iterator position, std::initializer_list<Value> list)
{
    return insert(position, list.begin(), list.end());
}

template <typename Value>
typename List<Value>::iterator List<Value>::erase(const_iterator position)
{
    if (!position)
    {
        return end();
    }

    auto node = position.mCurrentNode;
    if (!node->prev && !node->next)
    {
        mFirstNode = nullptr;
        mLastNode = nullptr;
    }
    else if (!node->prev && node->next) // first element
    {
        node->next->prev = nullptr;
        mFirstNode = node->next;
    }
    else if (node->prev && !node->next) // last element
    {
        node->prev->next = nullptr;
        mLastNode = node->prev;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    --mSize;
    return createIterator<iterator>(node->next, node->prev);
}

template <typename Value>
typename List<Value>::iterator List<Value>::erase(const_iterator it, const_iterator last)
{
    while (it != last)
    {
        erase(it++);
    }
    return last ? createIterator<iterator>(last.mCurrentNode) : end();
}

template <typename Value>
typename List<Value>::reference List<Value>::front()
{
    verifyNotEmpty();
    return mFirstNode->value;
}

template <typename Value>
typename List<Value>::const_reference List<Value>::front() const
{
    verifyNotEmpty();
    return mFirstNode->value;
}

template <typename Value>
typename List<Value>::reference List<Value>::back()
{
    verifyNotEmpty();
    return mLastNode->value;
}

template <typename Value>
typename List<Value>::const_reference List<Value>::back() const
{
    verifyNotEmpty();
    return mLastNode->value;
}

template <typename Value>
void List<Value>::push_back(const Value & val)
{
    emplace_back(val);
}

template <typename Value>
void List<Value>::push_back(Value && val)
{
    emplace_back(std::move(val));
}

template <typename Value>
void List<Value>::push_front(const Value & val)
{
    emplace_front(val);
}

template <typename Value>
void List<Value>::push_front(Value && val)
{
    emplace_front(std::move(val));
}

template <typename Value>
void List<Value>::pop_back()
{
    verifyNotEmpty();
    erase(--cend());
}

template <typename Value>
void List<Value>::pop_front()
{
    verifyNotEmpty();
    erase(cbegin());
}

template <typename Value>
void List<Value>::swap(List & x)
{
    std::swap(mFirstNode, x.mFirstNode);
    std::swap(mLastNode, x.mLastNode);
    std::swap(mSize, x.mSize);
}

template <typename Value>
void List<Value>::clear() noexcept
{
    erase(cbegin(), cend());
}

template <typename Value>
size_t List<Value>::size() const noexcept
{
    return mSize;
}

template <typename Value>
bool List<Value>::empty() const noexcept
{
    return !mSize;
}

template <typename Value>
typename List<Value>::iterator List<Value>::insertToEmpty(const NodePtr & newNode)
{
    mFirstNode = newNode;
    mLastNode = newNode;
    ++mSize;

    return createIterator<iterator>(newNode);
}

template <typename Value>
typename List<Value>::iterator List<Value>::insertAfter(const NodePtr & node, const NodePtr & newNode)
{
    newNode->prev = node;

    if (!node->next)
    {
        node->next = newNode;
        mLastNode = newNode;
    }
    else
    {
        newNode->next = node->next;
        node->next->prev = newNode;
        node->next = newNode;
    }
    ++mSize;

    return createIterator<iterator>(newNode);
}

template <typename Value>
template <typename T, typename>
T List<Value>::createIterator(const NodePtr & node, const NodePtr & prevNode)
{
    return T(nullptr, node, prevNode);
}

template <typename Value>
template <typename T, typename>
T List<Value>::createIterator(const NodePtr & node, const NodePtr & prevNode) const
{
    return T(nullptr, node, prevNode);
}

template <typename Value>
template <typename T, typename>
bool List<Value>::isIteratorValid(const T & it)
{
    return it;// && it.mCollection == shread_from_this();
}

template <typename Value>
void List<Value>::verifyNotEmpty() const
{
    if (empty())
    {
        throw std::logic_error("empty list");
    }
}