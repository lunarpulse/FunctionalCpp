/*
 * =============================================================================
 *
 *       Filename:  parrellism.cpp
 *
 *    Description:  pararellism of functional programming
 *
 *        Version:  1.0
 *        Created:  29/11/18 14:09:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

struct Image { };				// dummy
struct FaceImage { };				// dummy
std::vector < Image > images;
FaceImage extract_face (Image)
{
  return { };
}				// dummy

FaceImage empty_face_image;		// dummy
FaceImage add_face_images (FaceImage, FaceImage)
{
  return { };
}				// dummy

FaceImage divide_values (FaceImage, std::size_t)
{
  return { };
}				// dummy

int
main ()
{
  FaceImage
    result = empty_face_image;
for (const Image & image:images)
    {
      FaceImage
	face_image = extract_face (image);
      result = add_face_images (result, face_image);
    }
  result = divide_values (result, images.size ());

  result =
    fplus::transform_reduce_parallelly (extract_face, add_face_images,
					empty_face_image, images);

}

// Exercise 1:
//     Express the loop of the iterative version above as
//     a call to transform_reduce_parallelly.
//     The following types are given:
//     images : [Image]
//     extract_face : Image -> FaceImage
//     empty_face_image : FaceImage
//     add_face_images : (FaceImage, FaceImage) -> FaceImage
//     divide_values : (FaceImage, Int) -> FaceImage
//     transform_reduce_parallelly :
//     ((a -> b), ((b, b) -> b), b, [a]) -> b

// Exercise 2:
//     When done with exercise 1
//     have a look at the documentation for std::async
//     http://en.cppreference.com/w/cpp/thread/async
//     and think about cases in your old projects
//     where you could have used it to make your code
//     easier.
