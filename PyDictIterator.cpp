/* 
 * File:   PyDictIterator.cpp
 * Author: dotser02
 * 
 * Created on March 9, 2014, 6:53 PM
 */



#include "PyDict.h"
#include "PyDictIterator.h"
#include "PyException.h"
#include <sstream>
#include <string>
using namespace std;

PyDictIterator::PyDictIterator(unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>& theMap) : PyObject(), map(theMap) {

    cerr << "Got into __iter__" << endl;
    it = map.begin();
    
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDictIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyDictIterator::__next__);

}

PyDictIterator::~PyDictIterator() {
    
}

PyType* PyDictIterator::getType(){
    return PyTypes[PyDictIteratorType];
}

string PyDictIterator::toString() {
    ostringstream s;
    
    s << "<dict_iterator object at " << this << ">";
    
    return s.str();
}

PyObject* PyDictIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg;
    cout << "Got into __iter__" << endl;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

PyObject* PyDictIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;
    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    //**NOTE** Current exception statement might end iteration before final element is returned.
    if (it == map.end()) {
        PyObject* key = it->first;
        //What do I want to store it as?
        it++;
        return key;
    
        throw new PyException(PYSTOPITERATIONEXCEPTION, "Stopping Iteration");
    }
    cout << "Got into __iter__" << endl;
    PyObject* key = it->first;
    //What do I want to store it as?
    it++;
    return key;
    
}