#include <iostream>
#include <type_traits>

namespace lgz{


	template<int pos,typename Head,typename... Tails>
	struct ArgumentType:ArgumentType<pos-1,Tails...>{
	};

	template<typename Head,typename... Tails>
	struct ArgumentType<0,Head,Tails...>{
		using type = Head;
	};

	template<typename T> struct FunctionTrait;
	
	template<typename R>
	struct FunctionTrait<R(*)()>{
		const static int ARGUMENTS = 0;
		using RetType = R;
	};


	template<typename R,typename... ArgTypes>
	struct FunctionTrait<R(*)(ArgTypes...)>{
		const static int ARGUMENTS = sizeof...(ArgTypes);
		using RetType = R;
		
		template<int pos>
		static typename ArgumentType<pos,ArgTypes...>::type ArgType();
	};


	struct PlaceHolder{
		using type = PlaceHolder;
	};

	PlaceHodler __placeholder__;

	template<typename Func,typename... Args>
	struct Function{
		
	};

	template<typename Func>
	struct Function{
		Func* funcPtr{nullptr};
		Function(Func* func):funcPtr(func){}

		FunctionTrait<Func*>::RetType operator () const{
			if(funcPtr){
				funcPtr();
			}			
		}
	};

	template<typename Func,typename... FuncArgs,PlaceHolder... placeholders>
	Function<Func,FuncArgs...> bind(Func* funcptr,FuncArgs...&&,placeHolders...&&){
		return Function<Func,FuncArgs...>(funcptr,std::forward<FuncArgs&&>(FuncArgs)...);
	}

}

int main(){
	using namespace lgz;
	typedef void(*TestFunc)(int,double,const std::string&);
	std::cout<<FunctionTrait<TestFunc>::ARGUMENTS<<std::endl;
	std::cout<<std::is_same<decltype(FunctionTrait<TestFunc>::ArgType<2>()),const std::string&>::value<<std::endl;
	return 0;
}
