/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifdef MULTIDIMENSIONAL_MATRIX

template <class type>
MultidimensionalMatrix<type>::~MultidimensionalMatrix(){
  delete[] arr;
}
template <class type>
MultidimensionalMatrix<type>::MultidimensionalMatrix(const MatCoords& coords): arr(NULL) {
  AllocSize(coords);
}
template <class type>
MultidimensionalMatrix<type>::MultidimensionalMatrix(const MultidimensionalMatrix<type>& that): arr(NULL){
  *this = that;
}
template <class type>
const MultidimensionalMatrix<type>& MultidimensionalMatrix<type>::operator=(const MultidimensionalMatrix<type>& that){
  AllocSize(that.dimensions);
  memcpy(arr,that.arr,sizeof(type)*TotalSize());
}

template <class type>
const type& MultidimensionalMatrix<type>::Get(const MatCoords& coords) const{
  return GetIndex(CoordsToIndex(coords));
}
template <class type>
void MultidimensionalMatrix<type>::Set(const MatCoords& coords, const type& val){
  return SetIndex(CoordsToIndex(coords), val);
}
template <class type>
type& MultidimensionalMatrix<type>::Access(const MatCoords& coords){
  return AccessIndex(CoordsToIndex(coords));
}
template <class type>
type& MultidimensionalMatrix<type>::operator()(const MatCoords& coords){
  return Access(coords);
}

template <class type>
const type& MultidimensionalMatrix<type>::GetIndex(int x) const{
  return arr[x];
}
template <class type>
void MultidimensionalMatrix<type>::SetIndex(size_t x, const type& val){
  arr[x] = val;
}
template <class type>
type& MultidimensionalMatrix<type>::AccessIndex(size_t x){
  return arr[x];
}
template <class type>
type& MultidimensionalMatrix<type>::operator()(size_t x){
  return arr[x];
}

template <class type>
size_t MultidimensionalMatrix<type>::NumDimensions() const{
  return dimensions.Size();
}

template <class type>
size_t MultidimensionalMatrix<type>::DimSize(size_t x) const{
  return dimensions.Get(x);
}

template <class type>
size_t MultidimensionalMatrix<type>::TotalSize() const{
  return indexMultipliers.Get(0) * dimensions.Get(0);
}

template <class type>
size_t MultidimensionalMatrix<type>::PrintRow(size_t startIndex, size_t count) const{
  using namespace std;
  for(size_t i = 0; i < count; ++i){
    cout << GetIndex(startIndex + i)  << ' ';
  }
}

template <class type>
size_t MultidimensionalMatrix<type>::PrintSlice(size_t startIndex,
                                                size_t rowcount, size_t colCount) const{
  using namespace std;
  for(size_t row = 0; row < rowcount; ++row){
    PrintRow(startIndex+row*colCount, colCount);
    cout << endl;
  }
}

template <class type>
size_t MultidimensionalMatrix<type>::Print3D() const{
  using namespace std;
  for(size_t slice = 0; slice < DimSize(0); ++slice){
    cout << "slice: " << slice << endl;
    PrintSlice(slice*indexMultipliers.Get(0), DimSize(1), DimSize(2));
    cout << endl << endl;
  }
}

template <class type>
size_t MultidimensionalMatrix<type>::Print() const{
  if(NumDimensions() == 3){
    Print3D();
  }
  else if(NumDimensions() == 2){
    PrintSlice(0, DimSize(0), DimSize(1));
  }
  else{
    PrintRow(0, DimSize(0));
  }
}

//*********
//privates:
//*********
template <class type>
void MultidimensionalMatrix<type>::AllocSize(MatCoords newDims){
  dimensions = newDims;
  indexMultipliers.Resize(dimensions.Size());

  ReCalculateIndexMultipliers();
  delete[] arr;
  arr = new type[TotalSize()];
}

template <class type>
void MultidimensionalMatrix<type>::ReCalculateIndexMultipliers(){
  if(dimensions.Size() > 1){
    indexMultipliers(indexMultipliers.Size()-1) = 1;

    for(size_t i = indexMultipliers.Size()-2; i > 0; --i)
      indexMultipliers(i) = indexMultipliers(i+1) * dimensions(i+1);
   
    indexMultipliers(0) = indexMultipliers(1)*dimensions(1);
  }
  else{
    indexMultipliers(0) = 0;
  }
}

template <class type>
size_t MultidimensionalMatrix<type>::CoordsToIndex(const MatCoords& coords) const{
  size_t sum = 0;
  for(size_t i = 0; i < indexMultipliers.Size() && i < coords.Size(); ++i)
    sum+=coords.Get(i)*indexMultipliers.Get(i);
  return sum;
}

#endif
