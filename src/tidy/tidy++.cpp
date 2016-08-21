#include "tidy++.h"

using namespace std;

tidy_cpp::tidy_cpp(const std::__cxx11::string &in)
    : _in(in),_doc(tidyCreate()), _out(
{
    0
}), _err({0})
{
    tidySetErrorBuffer(_doc, &_err);
}

tidy_cpp::tidy_cpp(std::__cxx11::string &&in)
    : _in(in), _doc(tidyCreate()), _out(
{
    0
}), _err({0})
{
    tidySetErrorBuffer(_doc, &_err);
}

tidy_cpp::~tidy_cpp()
{
    if(_out.allocated) {
        tidyBufFree(&_out);
    }
    if(_err.allocated) {
        tidyBufFree(&_err);
    }
    tidyRelease(_doc);
}

int tidy_cpp::return_code()
{
    return _rcode;
}

std::__cxx11::string tidy_cpp::input()
{
    return _in;
}

std::__cxx11::string tidy_cpp::output()
{
    return _out.bp ? std::string((char*)_out.bp) : "";
}

std::__cxx11::string tidy_cpp::error()
{
    return _err.bp ? std::string((char*)_err.bp) : "";
}

int tidy_cpp::parse()
{
    return (_rcode = _rcode >= 0 ? tidyParseString(_doc, _in.c_str()) : _rcode);
}

int tidy_cpp::clean_and_repair()
{
    return (_rcode = _rcode >= 0 ? tidyCleanAndRepair(_doc) : _rcode);
}

int tidy_cpp::save_buffer()
{
    return (_rcode = _rcode >= 0 ? tidySaveBuffer(_doc, &_out) : _rcode);
}

int tidy_cpp::run_diagnostics()
{
    return (_rcode = _rcode >= 0 ? tidyRunDiagnostics(_doc) : _rcode);
}

void tidy_cpp::set_option(TidyOptionId option, bool value)
{
    tidyOptSetBool(_doc, option, value ? yes : no);
}

bool tidy_cpp::traverse(std::function<bool (TidyNode)> func)
{
    return traverse(func, tidyGetRoot(_doc));
}

bool tidy_cpp::traverse(std::function<bool (TidyNode)> func, TidyNode node)
{
    bool res = func(node);
    if(res) {
        for(TidyNode child = tidyGetChild(node); child; child = tidyGetNext(child)) {
            traverse(func, child);
        }
    }
    return res;
}

bool tidy_cpp::filter(std::function<bool (TidyNode)> func)
{
    return filter(func, tidyGetRoot(_doc));
}

bool tidy_cpp::filter(std::function<bool (TidyNode)> func, TidyNode node)
{
    bool res = func(node);
    if(res) {
        vector<TidyNode> discards;
        for(TidyNode child = tidyGetChild(node); child; child = tidyGetNext(child)) {
            if(!filter(func, child)){
                discards.push_back(child);
            }
        }
        discard(discards);
    }
    return res;
}

void tidy_cpp::discard(std::vector<TidyNode>& nodes)
{
    for(TidyNode node : nodes) {
        if(node) {
            tidyDiscardElement(_doc, node);
        }
    }
}

string tidy_cpp::name(TidyNode node)
{
    string name;
    switch ( tidyNodeGetType(node) ) {
    case TidyNode_Root:
        name = "root";
        break;
    case TidyNode_DocType:
        name = "doctype";
        break;
    case TidyNode_Comment:
        name = "comment";
        break;
    case TidyNode_ProcIns:
        name = "procins";
        break;
    case TidyNode_Text:
        name = "text";
        break;
    case TidyNode_CDATA:
        name = "cdata";
        break;
    case TidyNode_Section:
        name = "section";
        break;
    case TidyNode_Asp:
        name = "asp";
        break;
    case TidyNode_Jste:
        name = "jste";
        break;
    case TidyNode_Php:
        name = "php";
        break;
    case TidyNode_XmlDecl:
        name = "xmldecl";
        break;

    case TidyNode_Start:
    case TidyNode_End:
    case TidyNode_StartEnd:
    default:
        name = string(tidyNodeGetName( node ));
        break;
    }

    return name;
}
