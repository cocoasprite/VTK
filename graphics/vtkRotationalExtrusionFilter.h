/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRotationalExtrusionFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 1993-2000 Ken Martin, Will Schroeder, Bill Lorensen 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither name of Ken Martin, Will Schroeder, or Bill Lorensen nor the names
   of any contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkRotationalExtrusionFilter - sweep polygonal data creating "skirt" from free edges and lines, and lines from vertices
// .SECTION Description
// vtkRotationalExtrusionFilter is a modelling filter. It takes polygonal 
// data as input and generates polygonal data on output. The input dataset 
// is swept around the z-axis to create new polygonal primitives. These 
// primitives form a "skirt" or swept surface. For example, sweeping a
// line results in a cylindrical shell, and sweeping a circle creates a 
// torus.
//
// There are a number of control parameters for this filter. You can 
// control whether the sweep of a 2D object (i.e., polygon or triangle 
// strip) is capped with the generating geometry via the "Capping" instance
// variable. Also, you can control the angle of rotation, and whether 
// translation along the z-axis is performed along with the rotation.
// (Translation is useful for creating "springs".) You also can adjust 
// the radius of the generating geometry using the "DeltaRotation" instance 
// variable.
//
// The skirt is generated by locating certain topological features. Free 
// edges (edges of polygons or triangle strips only used by one polygon or
// triangle strips) generate surfaces. This is true also of lines or 
// polylines. Vertices generate lines.
//
// This filter can be used to model axisymmetric objects like cylinders,
// bottles, and wine glasses; or translational/rotational symmetric objects
// like springs or corkscrews.

// .SECTION Caveats
// If the object sweeps 360 degrees, radius does not vary, and the object 
// does not translate, capping is not performed. This is because the cap 
// is unnecessary.
//
// Some polygonal objects have no free edges (e.g., sphere). When swept,
// this will result in two separate surfaces if capping is on, or no surface
// if capping is off.

// .SECTION See Also
// vtkLinearExtrusionFilter

#ifndef __vtkRotationalExtrusionFilter_h
#define __vtkRotationalExtrusionFilter_h

#include "vtkPolyDataToPolyDataFilter.h"

class VTK_EXPORT vtkRotationalExtrusionFilter : public vtkPolyDataToPolyDataFilter 
{
public:
  vtkTypeMacro(vtkRotationalExtrusionFilter,vtkPolyDataToPolyDataFilter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Create object with capping on, angle of 360 degrees, resolution = 12, and
  // no translation along z-axis.
  // vector (0,0,1), and point (0,0,0).
  static vtkRotationalExtrusionFilter *New();

  // Description:
  // Set/Get resolution of sweep operation. Resolution controls the number
  // of intermediate node points.
  vtkSetClampMacro(Resolution,int,1,VTK_LARGE_INTEGER);
  vtkGetMacro(Resolution,int);

  // Description:
  // Turn on/off the capping of the skirt.
  vtkSetMacro(Capping,int);
  vtkGetMacro(Capping,int);
  vtkBooleanMacro(Capping,int);

  // Description:
  // Set/Get angle of rotation.
  vtkSetMacro(Angle,float);
  vtkGetMacro(Angle,float);

  // Description:
  // Set/Get total amount of translation along the z-axis.
  vtkSetMacro(Translation,float);
  vtkGetMacro(Translation,float);

  // Description:
  // Set/Get change in radius during sweep process.
  vtkSetMacro(DeltaRadius,float);
  vtkGetMacro(DeltaRadius,float);

protected:
  vtkRotationalExtrusionFilter();
  ~vtkRotationalExtrusionFilter() {};
  vtkRotationalExtrusionFilter(const vtkRotationalExtrusionFilter&) {};
  void operator=(const vtkRotationalExtrusionFilter&) {};

  void Execute();
  int Resolution;
  int Capping;
  float Angle;
  float Translation;
  float DeltaRadius;
};

#endif
