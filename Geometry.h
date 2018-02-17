//
//  Geometry.h
//  SCMS
//
//  Created by Zach Zahos on 2016-12-11.
//
//

#pragma once

#include "Types.h"
#include <algorithm>

template <typename S>
struct Size;

template <typename S>
struct Point {
	S x, y;
	
	inline Point<S> operator+(const Point<S> &other) {
		return {x + other.x, y + other.y};
	}
	inline Point<S> operator-(const Point<S> &other) {
		return {x - other.x, y - other.y};
	}
};

template <typename S>
struct Size {
	S width, height;
	
	u32 area()
		{ return width * height; }
};

template <typename S>
struct Extents;

template <typename P,typename S>
struct Rect {
	Point<P> origin;
	Size<S> size;
	
	inline Extents<P> extents() {
		return {origin, bottomRight()};
	}
	inline Point<P> bottomRight() {
		return {origin.x + (P)size.width, origin.y + (P)size.height};
	}
	inline bool isEmpty() {
		return (size.width == 0 || size.height == 0);
	}
	
	Rect<P,S> overlap(Rect<P,S> other) {
		Extents<P> extents = {
			{ std::max(origin.x, other.origin.x), std::max(origin.y, other.origin.y) },
			{ (P)std::min(origin.x + size.width, other.origin.x + other.size.width), (P)std::min(origin.y + size.height, other.origin.y + other.size.height) }
		};
		if (!extents.isEmpty()) {
			return {extents.start, {(S)(extents.end.x - extents.start.x), (S)(extents.end.y - extents.start.y)}};
		} else {
			return {{0,0},{0,0}};
		}
	}
};

template <typename S>
struct Extents {
	Point<S> start;
	Point<S> end;
	
	inline Rect<S, S> rect() {
		return {start, size()};
	}
	inline Size<S> size() {
		return end - start;
	}
	inline bool isEmpty() {
		return start.x >= end.x || start.y >= end.y;
	}
};
