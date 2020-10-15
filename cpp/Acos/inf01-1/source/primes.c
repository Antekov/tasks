#include <Python.h>

static PyObject* factor_out(PyObject* self, PyObject* args) {
    long number;
    if (!PyArg_ParseTuple(args, "l", &number)) {
        PyErr_SetString(PyExc_TypeError, "invalid input");
        return NULL;
    }
    if (number < 1) {
        PyErr_SetString(PyExc_TypeError, "your number is less than 1");
        return NULL;
    }

    PyObject* divisors = PyList_New(0);
    PyList_Append(divisors, PyLong_FromLong(1));
    long divisor_count = 1;
    for (long i = 2; number > 1;) {
        if (number % i == 0) {
            number /= i;
            ++divisor_count;
            PyList_Append(divisors, PyLong_FromLong(i));
        }
        else
            ++i;
    }

    if (divisor_count <= 2) {
        Py_DECREF(divisors);
        return Py_BuildValue("s", "Prime!");
    }
    else 
        return divisors;
}

static PyMethodDef methods[] = {
    {"factor_out", factor_out, METH_VARARGS, "help factor_out"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, "primes", "pyprimes", -1, methods
};

PyMODINIT_FUNC PyInit_primes(void) {
    return PyModule_Create(&module);
}