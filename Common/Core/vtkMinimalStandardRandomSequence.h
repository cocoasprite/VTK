/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMinimalStandardRandomSequence.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
=========================================================================*/
// .NAME vtkMinimalStandardRandomSequence - Park and Miller Sequence of pseudo random numbers
// .SECTION Description
// vtkMinimalStandardRandomSequence is a sequence of statistically independent
// pseudo random numbers uniformly distributed  between 0.0 and 1.0.
//
// The sequence is generated by a prime modulus multiplicative linear
// congruential generator (PMMLCG) or "Lehmer generator" with multiplier 16807
// and prime modulus 2^(31)-1. The authors calls it
// "minimal standard random number generator"
//
// ref: "Random Number Generators: Good Ones are Hard to Find,"
// by Stephen K. Park and Keith W. Miller in Communications of the ACM,
// 31, 10 (Oct. 1988) pp. 1192-1201.
// Code is at page 1195, "Integer version 2"
//
// Correctness test is described in first column, page 1195:
// A seed of 1 at step 1 should give a seed of 1043618065 at step 10001.

#ifndef __vtkMinimalStandardRandomSequence_h
#define __vtkMinimalStandardRandomSequence_h

#include "vtkCommonCoreModule.h" // For export macro
#include "vtkRandomSequence.h"

class VTKCOMMONCORE_EXPORT vtkMinimalStandardRandomSequence
  : public vtkRandomSequence
{
public:
  vtkTypeMacro(vtkMinimalStandardRandomSequence,vtkRandomSequence);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkMinimalStandardRandomSequence* New();
  
  // Description:
  // Set the seed of the random sequence.
  // The following pre-condition is stated page 1197, second column:
  // valid_seed: value>=1 && value<=2147483646
  // 2147483646=(2^31)-2
  // This method does not have this criterium as a pre-condition (ie it will
  // not fail if an incorrect seed value is passed) but the value is silently
  // changed to fit in the valid range [1,2147483646].
  // 2147483646 is added to a null or negative value.
  // 2147483647 is changed to be 1 (ie 2147483646 is subtracted).
  // Implementation note: it also performs 3 calls to Next() to avoid the
  // bad property that the first random number is proportional to the seed
  // value.
  void SetSeed(int value);
  
  // Description:
  // Set the seed of the random sequence. There is no extra internal
  // ajustment. Only useful for writing correctness test.
  // The following pre-condition is stated page 1197, second column
  // 2147483646=(2^31)-2
  // This method does not have this criterium as a pre-condition (ie it will
  // not fail if an incorrect seed value is passed) but the value is silently
  // changed to fit in the valid range [1,2147483646].
  // 2147483646 is added to a null or negative value.
  // 2147483647 is changed to be 1 (ie 2147483646 is subtracted).
  void SetSeedOnly(int value);
  
  // Description:
  // Get the seed of the random sequence.
  // Only useful for writing correctness test.
  int GetSeed();
  
  // Description:
  // Current value
  // \post unit_range: result>=0.0 && result<=1.0
  virtual double GetValue();
  
  // Description:
  // Move to the next number in the random sequence.
  virtual void Next();
  
  // Description:
  // Convenient method to return a value in a specific range from the
  // range [0,1. There is an initial implementation that can be overridden
  // by a subclass.
  // There is no pre-condition on the range:
  // - it can be in increasing order: rangeMin<rangeMax
  // - it can be empty: rangeMin=rangeMax
  // - it can be in decreasing order: rangeMin>rangeMax
  // \post result_in_range:
  // (rangeMin<=rangeMax && result>=rangeMin && result<=rangeMax)
  // || (rangeMax<=rangeMin && result>=rangeMax && result<=rangeMin)
  virtual double GetRangeValue(double rangeMin,
                               double rangeMax);
  
protected:
  vtkMinimalStandardRandomSequence();
  virtual ~vtkMinimalStandardRandomSequence();
  int Seed;
private:
  vtkMinimalStandardRandomSequence(const vtkMinimalStandardRandomSequence&);  // Not implemented.
  void operator=(const vtkMinimalStandardRandomSequence&);  // Not implemented.
};

#endif // #ifndef __vtkMinimalStandardRandomSequence_h
