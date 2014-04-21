#include <iostream>
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE MyTest
#include <time.h>
#include <cstdlib>
#include "MainGraphic.hpp"
#include <boost/test/unit_test.hpp>
#include "CorrespGrouping.hpp"

BOOST_AUTO_TEST_CASE(trying)
{
	CorrespGrouping<pcl::PointXYZRGBA> cg(new ShapeLocal<pcl::PointXYZRGBA>("bob1"), new ShapeLocal<pcl::PointXYZRGBA>("bob2"));
	cg.addObject(new ShapeLocal<pcl::PointXYZRGBA>("bob2")); //Problem with this declaration oO
	BOOST_CHECK_EQUAL(cg.getAllObjects().size(),1);
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>());
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZRGBA>());
	
	pcl::io::loadPCDFile ("/home/ros/catkin_ws/src/Tobot/stalker/src/Test/milk.pcd", *cloud);
	pcl::io::loadPCDFile ("/home/ros/catkin_ws/src/Tobot/stalker/src/Test/milk.pcd", *cloud2);
	
	cg.addObject(cloud);
	BOOST_CHECK_EQUAL(cg.getAllObjects().size(),2);
	//cg.addObject(cloud2);
	std::cout<<"Ten End"<<std::endl;
}