#include <algorithm>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/shared_connection_block.hpp>
#include <cstdio>
#include <iostream>
#include <boost/signals2.hpp>
#include <boost/optional/optional_io.hpp>
#include <iterator>
#include <ostream>
#include <boost/bind/bind.hpp>

using namespace std;

class Document
{
public:
    typedef boost::signals2::signal<void()> signal_t;
    Document()
    {}

    /* Connect a slot to the signal which will be emitted whenever
      text is appended to the document. */
    boost::signals2::connection connect(const signal_t::slot_type& subscriber)
    {
        return m_sig.connect(subscriber);
    }

    void append(const char* s)
    {
        m_text += s;
        m_sig();
    }

    const std::string& getText() const
    {
        return m_text;
    }

private:
    signal_t m_sig;
    std::string m_text;
};

class TextView
{
public:
    TextView(Document& document) : m_document(document)
    {
        m_connection = m_document.connect(boost::bind(&TextView::refresh, this));
    }
    ~TextView()
    {
        m_connection.disconnect();
    }

    void refresh() const
    {
        std::cout << "TextView: " << m_document.getText() << std::endl;
    }
private:
    Document& m_document;
    boost::signals2::connection m_connection;
};

class HexView
{
public:
    HexView(Document& doc) : m_document(doc)
    {
        m_connection = m_document.connect(boost::bind(&HexView::refresh, this));
    }

    ~HexView()
    {
        m_connection.disconnect();
    }

    void refresh() const
    {
        const std::string& s = m_document.getText();

        std::cout << "HexView:";

        for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
            std::cout << ' ' << std::hex << static_cast<int>(*it);

        std::cout << std::endl;
    }
private:
    Document& m_document;
    boost::signals2::connection m_connection;
};

int main()
{
    Document doc;
    TextView tv(doc);
    HexView hv(doc);

    doc.append("hello");

    return 0;
}