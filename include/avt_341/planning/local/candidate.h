/**
 * \class Candidate
 *
 * Class for candidate paths generated by the local planner.
 *
 * \author Chris Goodin
 *
 * \date 8/31/2020
 */

#ifndef SPLINE_CANDIDATE_H
#define SPLINE_CANDIDATE_H
#include <vector>
#include "avt_341/planning/local/polynomial.h"

namespace avt_341 {
namespace planning{

class Candidate {
public:
	/**
	 * Create an empty candidate path.
	 */
	Candidate(){}

	/**
	 * Create a candidate path and initialize with a polynomial.
	 * \param p The cubic polynomial to initialize the path to.
	 */ 
	Candidate(Polynomial p) {
		Initialize(p);
	}

	/**
	 * Initialize a candidate path with a polynomial.
	 * \param p The cubic polynomial to initialize the path to.
	 */ 
	void Initialize(Polynomial p) {
		curve_ = p;
		first_deriv_ = curve_.Derivative();
		second_deriv_ = first_deriv_.Derivative();
		out_of_bounds_ = false;
		hits_obstacle_ = false;
		rank_ = -1;
		max_curvature_ = 0.0f;
		max_length_ = 100.0f;
		s0_ = 0.0f;
	}

	/**
	 * Assignment operator for a candidate path.
	 */ 
	void operator = (const Candidate &c) {
		curve_ = c.curve_;
		first_deriv_ = c.first_deriv_;
		second_deriv_ = c.second_deriv_;
		out_of_bounds_ = c.out_of_bounds_;
		hits_obstacle_ = c.hits_obstacle_;
		cost_ = c.cost_;
		comfortability_ = c.comfortability_;
		static_safety_ = c.static_safety_;
		dynamic_safety_ = c.dynamic_safety_;
		segmentation_cost_ = c.segmentation_cost_;
		rank_ = c.rank_;
		max_length_ = c.max_length_;
		max_curvature_ = c.max_curvature_;
		s0_ = c.s0_;
	}

	/**
	 * Get the signed rho value of the candidate path at arc length s.
	 * \param s The arc length along the path.
	 */ 
	float At(float s) { return curve_.At(s); }

	/**
	 * Get the signed rho value of the first derivative of the candidate path at arc length s.
	 * \param s The arc length along the path.
	 */ 
	float DerivativeAt(float s) { return first_deriv_.At(s); }

	/**
	 * Get the signed rho value of the second derivative of the candidate path at arc length s.
	 * \param s The arc length along the path.
	 */ 
	float SecondDerivativeAt(float s) { return second_deriv_.At(s); }

	/**
	 * Return true if the candidate goes out of bounds.
	 */ 
	bool IsOutOfBounds() { return out_of_bounds_; }

		/**
	 * Return true if the candidate hits an obstacle.
	 */ 
	bool HitsObstacle() { return hits_obstacle_; }

	/**
	 * Set to true if the candidate goes out of bounds.
	 * \param oob True if the candidate goes out of bounds.
	 */ 
	void SetOutOfBounds(bool oob) { out_of_bounds_ = oob; }

		/**
	 * Set to true if the candidate hits an obstacle.
	 * \param ho True if the candidate hits an obstacle.
	 */ 
	void SetHitsObstacle(bool ho) { hits_obstacle_ = ho; }

	/**
	 * Set the cumulative cost of the path.
	 * \param cost The cumulative cost of the path.
	 */ 
	void SetCost(float cost) { cost_ = cost; }

	/**
	 * Get the cumulative cost of the path. 
	 */
	float GetCost() { return cost_; }

	/**
	 * Set the rank of the path.
	 * \param rank The rank of the path.
	 */ 
	void SetRank(int rank) { rank_ = rank; }

	/**
	 * Get the rank of the path. 
	 */
	int GetRank() { return rank_; }

	/**
	 * Set the max curvature of the path.
	 * \param mc The max curvature of the path.
	 */ 
	void SetMaxCurvature(float mc) { max_curvature_ = mc; }

	/**
	 * Get the max curvature of the path.
	 */ 
	float GetMaxCurvature() { return max_curvature_; }

	/**
	 * Set the comfortability of the path.
	 * \param comfort The comfortability of the path.
	 */ 
	void SetComfortability(float comfort) { comfortability_ = comfort; }

	/**
	 * Get the comfortability of the path.
	 */ 
	float GetComfortability() { return comfortability_; }

	/**
	 * Set the static safety of the path.
	 * \param stat_safe The static safety of the path.
	 */ 
	void SetStaticSafety(float stat_safe) { static_safety_ = stat_safe; }

	/**
	 * Get the static safety of the path.
	 */ 
	float GetStaticSafety() { return static_safety_; }

	/**
	 * Set the dynamic safety of the path.
	 * \param dyn_safe The dynamic safety of the path.
	 */ 
	void SetDynamicSafety(float dyn_safe) { dynamic_safety_ = dyn_safe; }

	/**
	 * Get the dynamic safety of the path.
	 */ 
	float GetDynamicSafety() { return dynamic_safety_; }

	/**
	 * Set the path deviation cost of the path.
	 * \param rho_cost The path deviation cost of the path.
	 */ 
	void SetRhoCost(float rho_cost) { rho_final_ = rho_cost; }

	/**
	 * Get the path deviation cost of the path.
	 */ 
	float GetRhoCost() { return rho_final_; }

	/**
	 * Set the max length of the path.
	 * \param ml The max length of the path.
	 */ 
	void SetMaxLength(float ml) { max_length_ = ml; }

	/**
	 * Get the max length of the path
	 */ 
	float GetMaxLength() { return max_length_; }

	/**
	 * Set the initial s-value of the path, with respect to the centerline s.
	 * \param s0 The initial s-value of the path.
	 */ 
	void SetS0(float s0) { s0_ = s0; }

	/**
	 * Get the initial s-value of the path.
	 */ 
	float GetS0() { return s0_; }

    /**
    * Sets the terrain segmentation cost based on labeled terrain traversed
    */
    void SetSegmentationCost(float segmentation_cost) { segmentation_cost_ = segmentation_cost; }

    /**
    * Gets the terrain segmentation cost based on the terrain traversed
    */
    float GetSegmentationCost() const { return segmentation_cost_; }

private:
	Polynomial curve_;
	Polynomial first_deriv_;
	Polynomial second_deriv_;
	bool out_of_bounds_;
	bool hits_obstacle_;
	float cost_;
	float comfortability_;
	float static_safety_;
	float segmentation_cost_;
	float dynamic_safety_;
	float rho_final_;
	float max_curvature_;
	float max_length_;
	float s0_;
	int rank_;
};

} // namespace planning
} // namespace avt_341


#endif