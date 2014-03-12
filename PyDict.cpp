/* 
 * File:   PyDict.cpp
 * Author: dotser02
 * 
 * Created on March 9, 2014, 6:34 PM
 */

#include "PyDict.h"
#include "PyDictIterator.h"
//Taken from PyFunList.cpp
#include "PyException.h"
#include "PyNone.h"
#include "PyInt.h"
#include "PyStack.h"
#include "PyStr.h"
#include "PyBool.h"
#include <sstream>
//Thought unordered_map might be needed
#include <unordered_map>
using namespace std;

std::size_t PyHash::operator() (const PyObject* key) const {
    vector<PyObject*> args;
    PyInt* hashVal = (PyInt*) const_cast<PyObject*> (key)->callMethod("__hash__", &args);
    return hashVal->getVal();
}

bool PyKeysEqual::operator() (const PyObject* key1, const PyObject* key2) const {
    vector<PyObject*> args;
    args.push_back(const_cast<PyObject*> (key2));
    PyBool* test = (PyBool*) const_cast<PyObject*> (key1)->callMethod("__eq__", &args);
    return test->getVal();
}

//Did PyHash and PyKeysEquals first

PyDict::PyDict() : PyObject() {
    cerr << "Made a Dict" << endl;
    //map = NULL;
    //Not sure what we set map too.
    dict["__getitem__"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::__getitem__);
    dict["__len__"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::__len__);
    dict["__iter__"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::__iter__);
    dict["__setitem__"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::__setitem__);
    dict["keys"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::keys);
    dict["values"] = (PyObject * (PyObject::*)(vector<PyObject*>*)) (&PyDict::values);
}
//destructor, was blank in PyFunList

PyDict::~PyDict() {
}

PyType* PyDict::getType() {
    return PyTypes[PyDictType];
}

string PyDict::toString() {
    unordered_map<PyObject*, PyObject*, PyHash, PyKeysEqual>::iterator it;
    ostringstream s;
    s << "{";
    it = map.begin();
    while (it != map.end()) {
        s << it->first->toString() << ": " << it->second->toString();
        it++;
        if (it != map.end())
            s << ", ";
    }
    s << "}";
    return s.str();
}

PyObject* PyDict::getVal(PyObject* key) {
    
        return map[key];
    }
    
    //Am I returning a PyObject? Yes.  Is it the correct format?



void PyDict::setVal(PyObject* key, PyObject* val) {
    map[key]=val;
    //What types of objects do I want to insert?
}

PyObject* PyDict::__getitem__(vector<PyObject*>* args) {
    //args->size()
    //(*args)[0]
    ostringstream msg;
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return map[(*args)[0]];
}

PyObject* PyDict::__setitem__(vector<PyObject*>* args) {
    //(*args)[0]
    ostringstream msg;
    if (args->size() != 2) {
        msg << "TypeError: expected 2 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    map[(*args)[0]]=(*args)[1];
    return new PyNone();

}

PyObject* PyDict::__len__(vector<PyObject*>* args) {
    ostringstream msg; 
    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    else{
        int a = map.size();
        return new PyInt(a);
    }

}

PyObject* PyDict::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION, msg.str());
    }
    cerr << "Made a DictIter" << endl;
    return new PyDictIterator(map);
}


PyObject* PyDict::keys(vector<PyObject*>* args) {
    /*
    int x = this->__len__();
    for (int i = 0; i<=x;i++){
        this->getItem(i);
    }*/
}

PyObject* PyDict::values(vector<PyObject*>* args) {

}