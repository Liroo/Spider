// coreException

#ifndef COREEXCEPTION_HPP
# define COREEXCEPTION_HPP

# include <exception>
# include <string>

# define PLUGIN_POSITION_ERROR "This plugin position is not available."

namespace MSU {
  namespace Exception {
    class CoreException: public std::exception {
      public:
        CoreException(const std::string &msg): _msg(msg) {};
        virtual ~CoreException() {};

      protected:
        std::string _msg;

      public:
        const char *what() const throw() { return _msg.c_str(); };
    };
  };
};

#endif
