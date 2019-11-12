#pragma once

namespace Eigen {
  namespace internal {

    /**
     * Permits the use of some c++11 onward features in Eigen
     * Eigen does not use some c++11 features due to backwards compatibility
     * (and some CUDA dependence?)
     * autodiff is c++17 so can edit somethings...
     */

    // Erf - Basically copied the internals for std::sin and replaced with erf
    namespace numext {

      template<typename T>
      EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      T erf(const T &x) {
	EIGEN_USING_STD_MATH(erf);
	return erf(x);
      }

#ifdef __CUDACC__
      template<> EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      float erf(const float &x) { return ::erff(x); }

      template<> EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      double erf(const double &x) { return ::erf(x); }
#endif

    }

    template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
    Packet perf(const Packet& a) { using std::erf; return erf(a); }

    template<typename Scalar>
    struct scalar_erf_op {
      EIGEN_EMPTY_STRUCT_CTOR(scalar_erf_op)
      EIGEN_DEVICE_FUNC inline const Scalar operator() (const Scalar& a) const { return erf(a); }
      template <typename Packet>
      EIGEN_DEVICE_FUNC inline Packet packetOp(const Packet& a) const { return internal::perf(a); }
    };


    // Erfc - Basically copied the internals for std::sin and replaced with erf
    namespace numext {
      template<typename T>
      EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      T erfc(const T &x) {
	EIGEN_USING_STD_MATH(erfc);
	return erfc(x);
      }

#ifdef __CUDACC__
      template<> EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      float erfc(const float &x) { return ::erfcf(x); }

      template<> EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
      double erfc(const double &x) { return ::erfc(x); }
#endif
    }

    template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
    Packet perfc(const Packet& a) { using std::erfc; return erfc(a); }

    template<typename Scalar>
    struct scalar_erfc_op {
      EIGEN_EMPTY_STRUCT_CTOR(scalar_erfc_op)
      EIGEN_DEVICE_FUNC inline const Scalar operator() (const Scalar& a) const { return erfc(a); }
      template <typename Packet>
      EIGEN_DEVICE_FUNC inline Packet packetOp(const Packet& a) const { return internal::perfc(a); }
    };

  }
}
