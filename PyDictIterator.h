/* 
 * File:   PyDictIterator.h
 * Author: dotser02
 *
 * Created on March 9, 2014, 6:53 PM
 */

#ifndef PYDICTITERATOR_H
#define	PYDICTITERATOR_H

#include "PyObject.h"
#include "PyType.h"
#include "PyDict.h"
#include <string>
using namespace std;

class PyDictIterator : public PyObject {
public:
    PyDictIterator(unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>& map);
    virtual ~PyDictIterator();

    PyType* getType();
    string toString();
    //Do I need that method?
protected:
    unordered_map<PyObject*,PyObject*,PyHash,PyKeysEqual>& map;
    unordered_map<PyObject*, PyObject*, PyHash, PyKeysEqual>::iterator it;
    
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);

};

#endif	/* PYDICTITERATOR_H */

