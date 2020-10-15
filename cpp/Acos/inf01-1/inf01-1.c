#include <Python.h>

PyObject* primes_factor_out(PyObject* self, PyObject* args) {
    long n, x, d;

    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    
    PyObject* result = PyList_New(0);
    PyList_Append(result, PyLong_FromLong(1));

    d = 2;
    x = n;
    while (n > 1) {
        while (n % d == 0) {
            PyList_Append(result, PyLong_FromLong(d));
            n = n / d;
        }
        d++;
    }

    if (PyList_Size(result) == 2) {
        Py_DECREF(result);
        return Py_BuildValue("s", "Prime!");
    }
 
    return Py_BuildValue("O", result);
}

static PyMethodDef primes_methods[] = {
    { "factor_out", (PyCFunction) primes_factor_out, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

static PyModuleDef primes_module = {
    PyModuleDef_HEAD_INIT,
    "primes",
    "Provides function factor_out for prime numbers",
    0,
    primes_methods
};

PyMODINIT_FUNC PyInit_primes() {
    return PyModule_Create(&primes_module);
}
