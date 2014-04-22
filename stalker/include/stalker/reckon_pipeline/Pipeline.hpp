#ifndef PIPELINE_RECKON_H
#define PIPELINE_RECKON_H

#include "Shape3D.hpp"
#include "Shape3DLocal.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <deque>


template <typename PointType>
class Pipeline{
	
	public : 
	Shape<PointType>* _object; //Don't need because it take a Shape* from main.
	Shape<PointType>* _scene; // Need to be initialise because it takes a Cloud in argument.
	std::vector<Shape<PointType> *> _objects; //Deck of all objects to compare
	std::vector<Shape<PointType> *> _scenes; //Deck of all scene to compare
	
	public : 
	Pipeline(Shape<PointType>* p, Shape<PointType>* p2) : _object(p), _scene(p2){}; //FREE PROBLEM
	virtual ~Pipeline(){
		std::cout << "delete Pipeline"<<std::endl;
		delete _object;
		delete _scene;
		std::cout << "delete Pipeline objects top size "<<_objects.size()<<std::endl;
		clearObjects();
		std::cout << "delete Pipeline scene top size "<<_scenes.size()<<std::endl;
		clearScenes();
		
	}
	virtual void doPipeline() = 0;
	virtual void init(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud,pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud2){
		_object->set(cloud);
		_scene->set(cloud2);
	}
	virtual void setObject(Shape<PointType>* o){delete _object; _object=o;}
	virtual void setScene(Shape<PointType>* o){delete _scene; _scene=o;}
	virtual void setObject(typename pcl::PointCloud<PointType>::Ptr& obj);
	virtual void setScene(typename pcl::PointCloud<PointType>::Ptr& cloud);	
	virtual Shape<PointType>* getObject(){return _object;}
	virtual Shape<PointType>* getScene(){return _scene;}
	virtual void deleteObject(){delete _object;}
	virtual void deleteScene(){delete _scene;}
	
	//New interface : 
	virtual const std::vector<Shape<PointType> *>& getAllObjects(){return _objects;}
	virtual const std::vector<Shape<PointType> *>& getAllScenes(){return _scenes;}
	
	virtual void addObject(Shape<PointType>* o);
	virtual void addScene(Shape<PointType>* o);
	virtual void addObject(typename pcl::PointCloud<PointType>::Ptr o);
	virtual void addScene(typename pcl::PointCloud<PointType>::Ptr& o);
	
	virtual void removeObject(const std::string& name);
	virtual void removeScene(const std::string& name);
	virtual void removeObject(int i);
	virtual void removeScene(int i);
	virtual void removeObject(Shape<PointType>* o);
	virtual void removeScene(Shape<PointType>* o);
	virtual void clearObjects();
	virtual void clearScenes();
	virtual void print(){
		std::cout<<std::endl<<"********* Objects *********"<<std::endl;
		for(typename std::vector<Shape<PointType>*>::iterator it = _objects.begin(); it!=_objects.end();){
		//std::cout<<"Cleaning object size : "<<_objects.size()<<std::endl;
			std::cout<<(**it).getName()<<" "<<(**it).getCloud()->size()<<std::endl;
			it++;
		}
		std::cout<<"**************************"<<std::endl;
		std::cout<<std::endl<<"********* Scenes *********"<<std::endl;
		for(typename std::vector<Shape<PointType>*>::iterator it = _scenes.begin(); it!=_scenes.end();){
		//std::cout<<"Cleaning object size : "<<_objects.size()<<std::endl;
			std::cout<<(**it).getName()<<" "<<(**it).getCloud()->size()<<std::endl;
			it++;
		}
		std::cout<<"**************************"<<std::endl;
		std::cout<<std::endl;
	};
	
};

template <typename T>
inline void Pipeline<T>::setScene(typename pcl::PointCloud<T>::Ptr& cloud)
{
	this->_scene->update(cloud);
}

template <typename T>
inline void Pipeline<T>::setObject(typename pcl::PointCloud<T>::Ptr& obj)
{
	this->_object->update(obj);
}

template <typename PointType>
inline void Pipeline<PointType>::addObject(Shape<PointType>* o){
	_objects.push_back(o);
	
}
template <typename PointType>
inline void Pipeline<PointType>::addScene(Shape<PointType>* o){
	_scenes.push_back(o);
}

template <typename PointType>
inline void Pipeline<PointType>::addObject(typename pcl::PointCloud<PointType>::Ptr o){
	std::string name="object";
	name=name+boost::lexical_cast<std::string>( _scenes.size() );
	_objects.push_back(new ShapeLocal<PointType>(name));
	_objects[_objects.size()-1]->update(o);
}

template <typename PointType>
inline void Pipeline<PointType>::addScene(typename pcl::PointCloud<PointType>::Ptr& o){
	std::string name="scene";
	name=name+boost::lexical_cast<std::string>( _scenes.size() );
	_scenes.push_back(new ShapeLocal<PointType>(name));
	_scenes[_scenes.size()-1]->update(o);
}

template <typename PointType>
inline void Pipeline<PointType>::removeObject(const std::string& name){
	for (typename std::vector<Shape<PointType>*>::iterator it=_objects.begin(); it!=_objects.end();){
		if((**it).getName()==name){
			delete(*it);
			_objects.erase(it);
		}
		else{
			it++;
		}
	}	
}

template <typename PointType>
inline void Pipeline<PointType>::removeScene(const std::string& name){
	for (typename std::vector<Shape<PointType>*>::iterator it = _scenes.begin(); it!=_scenes.end();){
		if((**it).getName()==name){
			delete(*it);
			_scenes.erase(it);
		}
		else{
			it++;
		}
	}	
}

template <typename PointType>
inline void Pipeline<PointType>::removeObject(Shape<PointType>* o){
	for (typename std::vector<Shape<PointType>*>::iterator it=_objects.begin(); it!=_objects.end();){
		if((*it)==o){
			delete(*it);
			_objects.erase(it);
		}
		else{
			it++;
		}
	}	
}

template <typename PointType>
inline void Pipeline<PointType>::removeScene(Shape<PointType>* o){
	for (typename std::vector<Shape<PointType>*>::iterator it=_scenes.begin(); it!=_scenes.end();){
		if((*it)==o){
			delete(*it);
			_scenes.erase(it);
		}
		else{
			it++;
		}
	}	
}

template <typename PointType>
inline void Pipeline<PointType>::removeObject(int i){
	std::cout<<"remove object n "<< i << "with "<< _objects.size()<< std::endl;
	if(size_t(i)<_objects.size()){
		typename std::vector<Shape<PointType>*>::iterator it=_objects.begin()+i;
		delete(*it);
		_objects.erase(it);
	}
}
	
template <typename PointType>
inline void Pipeline<PointType>::removeScene(int i){

}

template <typename PointType>
inline void Pipeline<PointType>::clearObjects(){
	std::cout<<"clear objects"<<std::endl;
	for(typename std::vector<Shape<PointType>*>::iterator it = _objects.begin(); it!=_objects.end();){
		//std::cout<<"Cleaning object size : "<<_objects.size()<<std::endl;
		delete(*it);
		_objects.erase(it);
	}	
}

template <typename PointType>
inline void Pipeline<PointType>::clearScenes(){
	std::cout<<"clear scenes"<<std::endl;
	for(typename std::vector<Shape<PointType>*>::iterator it = _scenes.begin(); it!=_scenes.end();){
		//std::cout<<"Cleaning scene size : "<<_scenes.size()<<std::endl;
		delete(*it);
		_scenes.erase(it);
	}	
}
#endif
	
