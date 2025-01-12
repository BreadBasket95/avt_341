/**
 * \class Plotter
 *
 * Class to plot the candidate paths, centerline, and map from the planner.
 * For debugging purposes.
 *
 * \author Chris Goodin
 *
 * \date 9/2/2020
 */
#ifndef SPLINE_PLOTTER_H
#define SPLINE_PLOTTER_H

#include "avt_341/avt_341_utils.h"
#include "avt_341/planning/local/candidate.h"
#include "avt_341/visualization/base_visualizer.h"

// ros includes
#include "avt_341/node/ros_types.h"


namespace avt_341 {
namespace planning{

class Plotter {
public:
	/**
	 * Create a plotter object. 
	 */
	Plotter(std::shared_ptr<avt_341::visualization::VisualizerBase> visualizer);

	/**
	 * Set the centerline to be plotted.
	 * \param path List of points representing the centerline to be plotted. 
	 */
	void SetPath(std::vector<utils::vec2> path);

	/**
	 * Add the candidate paths to be plotted.
	 * \param curves A list of candidate paths to be plotted. 
	 */
	void AddCurves(std::vector<Candidate> curves);

	/**
	 * Add the occupancy grid that will be plotted
	 * \param grid The occupancy grid to be plotted. 
	 */
	void AddMap(avt_341::msg::OccupancyGrid grid);

	/**
	 * Add a list of global waypoints to be plotted
	 *  \param waypoints The waypoints to be plotted 
	 */
	void AddWaypoints(avt_341::msg::Path waypoints);

	/**
	 * Display the graph. 
	 */
	void Display();


	/**
	 * Display and save the graph. 
	 * \param save True to save, False if not
	 * \param ofname The output file name with extension
	 * \param nx The number of horizontal pixels to save
	 * \param ny The number of vertical pixels to save
	 */
	virtual void Display(bool save, const std::string & ofname, int nx, int ny);

	utils::ivec2 GetDimensions(){
		utils::ivec2 dim(nx_, ny_);
		return dim;
	}

protected:
	std::vector<utils::vec2> path_;
	std::vector<utils::vec2> waypoints_;
	std::vector<Candidate> curves_;
  std::shared_ptr<avt_341::visualization::VisualizerBase> visualizer_;
  avt_341::msg::OccupancyGrid grid_;

	float x_lo_;
	float x_hi_;
	float y_lo_;
	float y_hi_;
	int nx_; 
	int ny_;
	float pixdim_;
	bool map_set_;
	utils::ivec2 CartesianToPixel(float x, float y);

};
} // namespace planning
} // namespace avt_341


#endif