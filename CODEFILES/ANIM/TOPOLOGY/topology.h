/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
  
/* FILE NAME   : topology.h
 * PURPOSE     : Animation project.
 *               Topology subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 06.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __topology_h_
#define __topology_h_

#include "../../comdef.h"
#include "../anim.h"

/* Vertex representative type */
typedef struct tagVERTEX_DEF
{
  VEC P;         /* Vertex position */
  VEC2 T;        /* Texture coordinates */
  VEC N;         /* Normale coordinates */
  VEC4 C;        /* Vertex color */
  VEC Tangent;   /* Tangent */
  VEC Bitangent; /* Bitangent */
} VERTEX_DEF;

/* Topology representative type */
typedef struct tngTOPOLOGY
{
  INT W, H, NumOfVertexes; /* Size of topology, number of vertexes */
  VERTEX_DEF *V;           /* Vertex struct */
} TOPOLOGY;

#endif /* __topology_h_ */

/* END OF 'topology.h' FILE */

