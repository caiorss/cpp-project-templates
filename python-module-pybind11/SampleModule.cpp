#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#if defined(__MINGW32__) || defined(__MINGW64__)
  #include <math.h>
#else
  #include <cmath>
#endif

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;
using namespace pybind11::literals;

 
#ifdef OVERFLOW
  #undef OVERFLOW
#endif

#ifdef UNDERFLOW
  #undef UNDERFLOW
#endif

// ===================== Function Implementation ===================//

         //-----------------------------------------//
         //   C++ FUNCTIONS WITHOUT PYTHON OBJECTS  //
         //----------------------------------------·//

const char* version()
{
    return "SampleModule Version 3.451-ZETA";
}

int add(int i, int j)
{
    return i + j;
}

std::vector<double>
vectorCumulativeSum(std::vector<double> const& xs)
{
    std::vector<double> out(xs.size());
    double sum = 0.0;
    for(size_t i = 0; i < xs.size(); i++)
    {
        sum += xs[i];
        out[i] = sum;
    }
    return out;
}

void tabulate1(double start, double stop, double step,
               std::function<double (double)> func)
{
    if(start > stop || step <= 0)
        throw std::runtime_error(" Error: Invalid domain "
                                 "\n Expected: start < stop && step > 0 "
                                 );

    std::cout << std::setprecision(5) << std::fixed;
    for(double x = start; x <= stop; x+= step)
        std::cout << std::setw(10) << x
                  << std::setw(10) << func(x)
                  << std::endl;
}

enum class MathErrorCode: std::uint32_t
{
        OK           = 0x00
      , OVERFLOW     = 0x01
      , UNDERFLOW    = 0x04
      , NOT_A_NUMBER = 0x08
};


// Sample "function-object class"
class LinearFunctor
{
public:
    double A = 0, B = 0;

    LinearFunctor();
    LinearFunctor(double a, double b): A(a), B(b){ }

    double GetA() const   { return A; }
    void   SetA(double a) { A = a; }
    double GetB() const   { return B; }
    void   SetB(double b) { B = b; }

    void show() const
    {
        std::cout << " LinearFunction: y(x) = A * x + B" << std::endl;
        std::cout << " => A = " << this->A << " ; B = " << this->B << std::endl;
    }
    std::string toString() const
    {
        std::stringstream ss;
        ss << " LinearFunction: y(x) = A * x + B" << std::endl;
        ss << " => A = " << this->A << " ; B = " << this->B << std::endl;
        return ss.str();
    }
    // Function-call operator
    double operator()(double x)
    {
        return A * x + B;
    }
};



         //-----------------------------------------//
         //   Functions with Python Objects         //
         //----------------------------------------·//


// Sample function that takes a python tuple as argument and
// returns a dictionary.
py::dict
computeFormula(py::args args)
{
    py::print(" [INFO] Number of args = {s1} ; args = {s2}",
              "s1"_a = args.size(), "s2"_a = args);
    std::cout << " [INFO] Arguments are = " << py::str(args) << std::endl;
    int    n = py::cast<int>(args[0]);
    double x = py::cast<double>(args[1]);
    double y = py::cast<double>(args[2]);

    py::dict d{ "n"_a =  n, "2x"_a = 2.0 * x, "addxy"_a = (x + y)};
    d["m"] = 5.0 * x + 4.5 * y;
    py::print(" [INFO] Dictionary d = {d} ", "d"_a = d);
    return d;
}

// Function that takes a Python dictionary as argument
void showDictionary(py::dict map)
{
    std::cout << " ====== Show dictonary =========== " << std::endl;
    for(auto const& item : map)
        std::cout << " key = "
                  << item.first << " ; "
                  << item.second
                  << std::endl;
}

// Sample Python function taking a tuple and dictionary as argument
void pyFuncArgsKwargs(py::args args, py::kwargs kwargs)
{
    double x = py::cast<double>(args[0]);
    int    n = py::cast<double>(args[1]);
    bool   verbose = false;

    py::print(" [TRACE]   args = ", args);
    py::print(" [TRACE] kwargs = ", kwargs);

    std::cout << std::boolalpha;

    if(kwargs.contains("verbose"))
    {
        verbose = py::cast<bool>(kwargs["verbose"]);
    }
    std::cout << " [INFO] verbose option = "
              << verbose << std::endl;

    std::cout << " sqrt(x) = " << std::sqrt(x)
              << " ; 2 * n = " << 2 * n
              << std::endl;
}


// Sample function that takes a Python dictionary returning a
// Python tuple as argument.
py::tuple
dictionaryArgument(py::dict dict)
{
    std::cout << " >> Dictionary = " << py::str(dict) << std::endl;
    auto xx = dict["x"];
    auto yy = dict["y"];
    double x = py::cast<double>(xx);
    double y = py::cast<double>(yy);
    std::string name = py::cast<std::string>(dict["name"]);
    double z = std::sqrt(x * x + y * y);

    // Return a tuple on python side
    py::tuple tpl = py::make_tuple(x, y, z, name);
    py::print(" [INFO] Tuple = {} ", tpl);
    return tpl;
}

// Call Python Objec's Method (Duck typing)
void callPyObjectMethod(py::object obj, double k)
{
    // Print objec's name attribute
    py::print(" [TRACE] obj.name = ", obj.attr("name"));

    std::string name = py::cast<std::string>(obj.attr("name"));
    std::cout << " [COUT] object.name = " << name << std::endl;

    // Invoke object's method .call
    auto call = obj.attr("call");
    py::print(" [TRACE] obj.call(6.0) = ", call(6.0));
    double x = py::cast<double>(call(k));
    py::print(" [TRACE] 100.0 * objct.call(x) = ", 100.0 * x);
}

// ============= Module Registration ================================//

PYBIND11_MODULE(SampleModule, m) {
    // optional module docstring
    m.doc() = "Sample Python built with C++ CeePlusPlus ";

    //----------- Register C++ Functions --------//
    //

    m.def("version", &version, "Show Library Version");

    // Register an ordinary C++ function
    m.def("add",                                 // Function Name in Python side
          &add,                                  // Function Pointer
          "A function which adds two numbers",   // Docstring
          py::arg("x"),                          // Name of argument 1
          py::arg("y") = 10);                    // Name of argument 2 with default value

    m.def("cppLambda"
          ,[](double x, double y){ return 3.0 * x + y;}
          ,"A C++ lambda object or functor"
          //,py::arg("x"), py::args("y") = 15
    );

    m.def("vectorCumulativeSum", &vectorCumulativeSum);

    m.def("tabulate1", &tabulate1);

    py::enum_<MathErrorCode>(m, "MathErrorCode", py::arithmetic())
       .value("OK",           MathErrorCode::OK)
       .value("OVERFLOW",     MathErrorCode::OVERFLOW)
       .value("UNDEFLOW",     MathErrorCode::UNDERFLOW)
       .value("NOT_A_NUMBER", MathErrorCode::NOT_A_NUMBER);
      // .export_values();

    // Register LinearFunction
    py::class_<LinearFunctor>(m, "LinearFunctor")
            .def(py::init<double, double>())             // Register overloaded consructor
            .def("GetA", &LinearFunctor::GetA)            // Reister method GetA()
            .def("GetB", &LinearFunctor::GetB)            // Register method GetB()
            .def("SetA", &LinearFunctor::SetA)            // Reister method GetA()
            .def("SetB", &LinearFunctor::SetB)            // Register method GetB()
            .def("show", &LinearFunctor::show)            // Register method show
            .def("call", &LinearFunctor::operator())      // Register function-call operator with name 'call'
            .def("__call__", &LinearFunctor::operator ()) // Register fun-call operator
            .def("__repr__", &LinearFunctor::toString)    // Register strin representation
            .def_readwrite("A", &LinearFunctor::A)        // Register field A
            .def_readwrite("B", &LinearFunctor::B);       // Register field B


    // ------ Register Functions with Knowledge of Python API ----//
    //

    m.def("computeFormula", &computeFormula);

    m.def("showDictionary",
          &showDictionary,
          "Display dictionary in console" );

    m.def("pyFuncArgsKwargs",
          &pyFuncArgsKwargs,
          "Sample Python function taking a tuple");

    m.def("dictionaryArgument", &dictionaryArgument);
    m.def("callPyObjectMethod", &callPyObjectMethod);

} /** --- End of PYBIND11_MODULE registration --- */

