#ifndef _Array_H_
#define _Array_H_

#include <list>
using std::list;

namespace KeiUI{
	template<class I, class V>
	struct ArrayNode
	{
		I index;
		V value;

		ArrayNode(I index, V value)
		{
			this->index = index;
			this->value = value;
		}
	};

	template<class I, class V>
	class Array{
	private:
		list<ArrayNode<I, V>> nodeList;

	public:
		Array(){
			this->nodeList = list<ArrayNode<I, V>>();
		}

		void add(I index, V value){
			this->nodeList.push_back(ArrayNode<I, V>(index, value));
		}

		int size(){
			return this->nodeList.size();
		}

		bool exist(I index){
			list<ArrayNode<I, V>>::iterator iter;
			for(iter = this->nodeList.begin(); iter != this->nodeList.end(); iter++){
				if(iter->index == index){
					return true;
				}
			}

			return false;
		}

		V get(I index){
			list<ArrayNode<I, V>>::iterator iter;
			for(iter = this->nodeList.begin(); iter != this->nodeList.end(); iter++){
				if(iter->index == index){
					return iter->value;
				}
			}

			return V();
		}

		void clear(){
			this->nodeList.clear();
		}

		void remove(I index){

			list<ArrayNode<I, V>>::iterator iter;
			for(iter = this->nodeList.begin(); iter != this->nodeList.end(); iter++){

				if(iter->index == index){
					this->nodeList.erase(iter);
					return;
				}
			}
		}

		void set(I index, V value){

			list<ArrayNode<I, V>>::iterator iter;
			for(iter = this->nodeList.begin(); iter != this->nodeList.end(); iter++){

				if(iter->index == index){
					iter->value = value;
					return;
				}
			}
		}

		void remove(){
			list<ArrayNode<I, V>>::iterator iter = this->nodeList.end();
			iter--;

			this->nodeList.erase(iter);
		}

		V last(){
			list<ArrayNode<I, V>>::iterator iter = this->nodeList.end();
			iter--;

			return iter->value;
		}

	};

};

#endif _Array_H_