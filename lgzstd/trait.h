#ifndef __LGZSTD_TRAIT_H__
#define __LGZSTD_TRAIT_H__

namespace lgzstd{
	
	template<typename T1,typename... Others>
        struct is_integeral_helper:std::false_type{};

        template<typename T>
        struct is_integeral_helper<T,typename std::enable_if<T(1)==1,bool>::type>:std::true_type{};

        template<typename T>
        using is_integeral = is_integeral_helper<T,bool>;

	template<typename T>
	struct is_bool:std::false_type{};

	template<>
	struct is_bool<bool>:std::true_type{};

	
	template<typename T>
	struct is_double:std::false_type{};
	
	template<>
	struct is_double<double>:std::true_type{};

	template<>
	struct is_double<float>:std::true_type{};


}

#endif
