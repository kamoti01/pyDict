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
#include <sstream>
//Thought unordered_map might be needed
#include <unordered_map>
using namespace std;

std::size_t PyHash::operator() (const PyObject* key) const {
    vector<PyObject*> args;
    PyInt* hashVal = (PyInt*) const_cast<PyObject*>(key)->callMethod("__hash__",&args);
    return hashVal->getVal();
}

bool PyKeysEqual::operator() (const PyObject* key1, const PyObject* key2) const {
    vector<PyObject*> args;
    args.push_back(const_cast<PyObject*>(key2));
    PyBool* test = (PyBool*) const_cast<PyObject*>(key1)->callMethod("__eq__",&args);
    return test->getVal();
}

//Did PyHash and PyKeysEquals first


PyDict::PyDict() : PyObject() {
   
    //map = NULL;
    //Not sure what we set map too.
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__iter__);
    dict["__setitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::__setitem__);
    dict["keys"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::keys);
    dict["values"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDict::values);
}
//destructor, was blank in PyFunList
PyDict::~PyDict() {
}

PyType* PyDict::getType() {
    return PyTypes[PyDictType];
}


string PyDict::toString() {
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>::iterator it;
    ostringstream s;
    s << "{";
    it = map.begin();
    while (it!=map.end()) {
        s << it->first->toString() << ": " << it->second->toString();
        it++;
        if (it!=map.end())
            s << ", ";
    }
    s << "}";
    return s.str();
}

PyObject* PyDict::getVal(PyObject* key) {
    /*Create a catch for keys not in dict
        if (index >= data.size()) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
     */
    
    //Need to return map of that key.
    
}

void PyDict::setVal(PyObject* key, PyObject* val) {
    //Need to add a key/value pair to the map
}

PyObject* __getitem__(vector<PyObject*>* args) {
    
}

PyObject* __setitem__(vector<PyObject*>* args) {
    
}

PyObject* __len__(vector<PyObject*>* args) {
    
}


PyObject* PyDict::__iter__(vector<PyObject*>* args) {
    ostringstream msg;
            
    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
    }

    return new PyDictIterator(map);
}

PyObject* keys(vector<PyObject*>* args) {
    
}

PyObject* values(vector<PyObject*>* args) {
    
}