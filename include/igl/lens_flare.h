#ifndef IGL_LENS_FLARE_H
#define IGL_LENS_FLARE_H

#include <igl/OpenGL_convenience.h>
#include <Eigen/Core>

#include <vector>

namespace igl
{
  struct Flare{
    int type;             /* flare texture index, 0..5 */
    float scale;
    float loc;            /* postion on axis */
    float color[3];
    Flare(){}
    Flare(int type, float location, float scale, const float color[3], float colorScale) :
      type(type),
      scale(scale),
      loc(location)
    {
      this->color[0] = color[0] * colorScale;
      this->color[1] = color[1] * colorScale;
      this->color[2] = color[2] * colorScale;
    }
  };
  
  
  // Initialize shared data for lens flates
  //
  // Inputs:
  //   start_id   starting texture id location (should have at least id:id+16 free)
  // Outputs:
  //   shine  list of texture ids for shines
  //   flare  list of texture ids for flares
  void lens_flare_load_textures(
    std::vector<GLuint> & shine_ids,
    std::vector<GLuint> & flare_ids);
  
  // Create a set of lens flares
  //
  // Inputs:
  //   A  primary color
  //   B  secondary color
  //   C  secondary color
  // Outputs:
  //   flares  list of flare objects
  void lens_flare_create(
    const float * A,
    const float * B,
    const float * C,
    std::vector<Flare> & flares);
  
  // Draw lens flares
  //
  // Inputs:
  //   flares  list of Flare objects
  //   shine_ids  list of shine textures
  //   flare_ids  list of flare texture ids
  //   light  position of light
  //   near_clip  near clipping plane
  //   shine_tic  current "tic" in shine textures
  // Outputs:
  //   shine_tic  current "tic" in shine textures
  void lens_flare_draw(
    const std::vector<Flare> & flares,
    const std::vector<GLuint> & shine_ids,
    const std::vector<GLuint> & flare_ids,
    const Eigen::Vector3f & light,
    const float near_clip,
    int & shine_tic);
};

#ifdef IGL_HEADER_ONLY
#  include "lens_flare.cpp"
#endif

#endif
