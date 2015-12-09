/***************************************************************************
 *   Copyright (C) 2009-2015 by Veselin Georgiev, Slavomir Kaslev et al    *
 *   admin@raytracing-bg.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/**
 * @File mesh.h
 * @Brief Contains the Mesh class.
 */
#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "geometry.h"
#include "vector.h"
#include "bbox.h"

class Mesh: public Geometry {
	std::vector<Vector> vertices;
	std::vector<Vector> normals;
	std::vector<Vector> uvs;
	std::vector<Triangle> triangles;
	BBox bbox;

	void computeBoundingGeometry();
	bool intersectTriangle(const Ray& ray, const Triangle& t, IntersectionInfo& info);
public:
	
	bool faceted;

	Mesh() {
		faceted = false;
	}
	~Mesh();
	
	bool loadFromOBJ(const char* filename);
	
	void fillProperties(ParsedBlock& pb)
	{
		pb.getBoolProp("faceted", &faceted);
		char fn[256];
		if (pb.getFilenameProp("file", fn)) {
			if (!loadFromOBJ(fn)) {
				pb.signalError("Could not parse OBJ file!");
			}
			
		} else {
			pb.requiredProp("file");
		}
	}
	
	void beginRender();
	
	bool intersect(const Ray& ray, IntersectionInfo& info);
};

#endif // __MESH_H__
