#include <Python.h>
#include <vector>
#include "Maths.h"
/*
 * Implements an example function.
 */
PyDoc_STRVAR(Accelerate_Py_doc, "Accelerate_Py(maxtrix_of_values, arraye_of_lambdas, number)\\Example function");

PyObject *Accelerate_Py(PyObject *self, PyObject *args)//, PyObject *a_lambdas, PyObject *a_it_count) 
{
    
    /* Shared references that do not need Py_DECREF before returning. */
    PyObject* values = NULL;
    PyObject* lambdas = NULL;
    int it_count;

    if (!PyArg_ParseTuple(args, "OOi", &values, &lambdas, &it_count))
        return NULL;
    //return values;
    //return lambdas;
    //return PyLong_FromLong(it_count);

    int number = it_count;// PyLong_AsLong(it_count);
    
    std::vector<double> l;
    auto l_size = PyList_Size(lambdas);
    if (l_size == 0)
        return PyLong_FromLong(number);
    l.resize(l_size);
    for (auto i = 0; i < l_size; i++)
    {
        l[i] = PyFloat_AsDouble(PyList_GetItem(lambdas, i));
    }

    std::vector<std::vector<double>> v;    
    auto x_size = PyList_Size(values);
    if (x_size == 0)
        return PyLong_FromLong(number + l_size);
    auto y_size = PyList_Size(PyList_GetItem(values, Py_ssize_t(0)));
    if (y_size == 0)
        return PyLong_FromLong(number + l_size + x_size);
    v.resize(x_size);

    for (auto i = 0; i < x_size; i++)
    {
        v[i].resize(y_size);
        for (auto j = 0; j < x_size; j++)
        {
            v[i][j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(values, i), j));
        }
    }


    calculateWithOut(v, l, number);
    for (auto i = 0; i < x_size; i++)
    {
        v[i].resize(y_size);
        for (auto j = 0; j < x_size; j++)
        {
            PyList_SetItem(PyList_GetItem(values, i), j, PyFloat_FromDouble(v[i][j]));
        }
    }


    return values;
    ///* Parse positional and keyword arguments */
    //static char* keywords[] = { "obj", "number", NULL };
    //if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
    //    return NULL;
    //}

    /* Function implementation starts here */

    //if (number < 0) {
    //    PyErr_SetObject(PyExc_ValueError, obj);
    //    return NULL;    /* return NULL indicates error */
    //}

    Py_RETURN_NONE;
}

/*
 * List of functions to add to Accelerate_Py in exec_Accelerate_Py().
 */
static PyMethodDef Accelerate_Py_functions[] = {
    { "Accelerate_Py_Func", (PyCFunction)Accelerate_Py, METH_VARARGS | METH_KEYWORDS, Accelerate_Py_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize Accelerate_Py. May be called multiple times, so avoid
 * using static state.
 */
int exec_Accelerate_Py(PyObject *module) {
    PyModule_AddFunctions(module, Accelerate_Py_functions);

    PyModule_AddStringConstant(module, "__author__", "azat.sibgatullin");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2018);

    return 0; /* success */
}

/*
 * Documentation for Accelerate_Py.
 */
PyDoc_STRVAR(Accelerate_Py_module_doc, "The Accelerate_Py module");


static PyModuleDef_Slot Accelerate_Py_slots[] = {
    { Py_mod_exec, exec_Accelerate_Py },
    { 0, NULL }
};

static PyModuleDef Accelerate_Py_def = {
    PyModuleDef_HEAD_INIT,
    "Accelerate_Py",
    Accelerate_Py_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    Accelerate_Py_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_Accelerate_Py() {
    return PyModuleDef_Init(&Accelerate_Py_def);
}
