#include <cmath>
#include <list>
#include <algorithm>


#include "collisionchecker.h"
#include "collisionmodel.h"
#include "triangle3d.h"
#include "quadtreenode.h"
#include "../engineTester/main.h"

Vector3f CollisionChecker::collidePosition;
Triangle3D* CollisionChecker::collideTriangle;
//CollisionModel* CollisionChecker::stageCollideModel;
std::list<CollisionModel*> CollisionChecker::collideModels;
bool CollisionChecker::checkPlayer;



void CollisionChecker::initChecker()
{
	CollisionChecker::collidePosition.x = 0;
	CollisionChecker::collidePosition.y = 0;
	CollisionChecker::collidePosition.z = 0;

	CollisionChecker::collideTriangle = nullptr;

	CollisionChecker::checkPlayer = false;
}

void CollisionChecker::setCheckPlayer()
{
	CollisionChecker::checkPlayer = true;
}


void CollisionChecker::falseAlarm()
{
	for (CollisionModel* cm : CollisionChecker::collideModels)
	{
		cm->playerIsOn = false;
	}
}

bool CollisionChecker::checkCollision(
	float px1, float py1, float pz1,
	float px2, float py2, float pz2)
{
	bool triangleCollide = false;
	CollisionModel* finalModel = nullptr;
	double firstAbove = -2;
	double secondAbove = -2;
	double tx1 = 0, tx2 = 0, tx3 = 0, ty1 = 0, ty2 = 0, ty3 = 0, tz1 = 0, tz2 = 0, tz3 = 0;
	double A, B, C, D;
	double numerator, denominator, u;

	double minDist = -1;

	double checkRadius = 8 + sqrt(pow(px2 - px1, 2) + pow(py2 - py1, 2) + pow(pz2 - pz1, 2));


	//CollisionChecker::collideModels.push_back(CollisionChecker::stageCollideModel);
	for (CollisionModel* cm : CollisionChecker::collideModels)
	{
		if (CollisionChecker::checkPlayer)
		{
			cm->playerIsOn = false;
		}

		//Bounds check on entire model
		if (px1 - checkRadius <= cm->maxX && px1 + checkRadius >= cm->minX &&
			pz1 - checkRadius <= cm->maxZ && pz1 + checkRadius >= cm->minZ &&
			py1 - checkRadius <= cm->maxY && py1 + checkRadius >= cm->minY)
		{
			if (cm->hasQuadTree() == true)
			{
				QuadTreeNode* node = cm->quadTreeRoot;
				QuadTreeNode* deepestNode = nullptr;

				std::list<QuadTreeNode*> alreadySearchedNodes;

				int treeMaxDepth = cm->treeMaxDepth;

				//search for (px1, pz1)
				while (node != nullptr)
				{
					if (std::find(alreadySearchedNodes.begin(), alreadySearchedNodes.end(), node) == alreadySearchedNodes.end())
					{
						alreadySearchedNodes.push_back(node);

						//check through node.tris;
						for (Triangle3D* currTriangle : node->tris)
						{
							//Bounds check on individual triangle
							if (px1 - checkRadius <= currTriangle->maxX && px1 + checkRadius >= currTriangle->minX &&
								pz1 - checkRadius <= currTriangle->maxZ && pz1 + checkRadius >= currTriangle->minZ &&
								py1 - checkRadius <= currTriangle->maxY && py1 + checkRadius >= currTriangle->minY)
							{
								tx1 = currTriangle->p1X;
								tx2 = currTriangle->p2X;
								tx3 = currTriangle->p3X;
								ty1 = currTriangle->p1Y;
								ty2 = currTriangle->p2Y;
								ty3 = currTriangle->p3Y;
								tz1 = currTriangle->p1Z;
								tz2 = currTriangle->p2Z;
								tz3 = currTriangle->p3Z;
								A = currTriangle->A;
								B = currTriangle->B;
								C = currTriangle->C;
								D = currTriangle->D;

								numerator = (A*px1 + B*py1 + C*pz1 + D);
								denominator = (A*(px1 - px2) + B*(py1 - py2) + C*(pz1 - pz2));

								if (denominator != 0)
								{
									u = (numerator / denominator);
									double cix = px1 + u*(px2 - px1);
									double ciy = py1 + u*(py2 - py1);
									double ciz = pz1 + u*(pz2 - pz1);

									if (B != 0)
									{
										double planey1 = (((-A*px1) + (-C*pz1) - D) / B);
										double planey2 = (((-A*px2) + (-C*pz2) - D) / B);
										firstAbove = copysign(1, py1 - planey1);
										secondAbove = copysign(1, py2 - planey2);
									}
									else if (A != 0)
									{
										double planex1 = (((-B*py1) + (-C*pz1) - D) / A);
										double planex2 = (((-B*py2) + (-C*pz2) - D) / A);
										firstAbove = copysign(1, px1 - planex1);
										secondAbove = copysign(1, px2 - planex2);
									}
									else if (C != 0)
									{
										double planez1 = (((-B*py1) + (-A*px1) - D) / C);
										double planez2 = (((-B*py2) + (-A*px2) - D) / C);
										firstAbove = copysign(1, pz1 - planez1);
										secondAbove = copysign(1, pz2 - planez2);
									}

									if (secondAbove != firstAbove &&
										checkPointInTriangle3D(cix, ciy, ciz, tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3,
											abs(currTriangle->normal.x),
											abs(currTriangle->normal.y),
											abs(currTriangle->normal.z)))
									{
										//what is the distance to the triangle? set it to maxdist
										triangleCollide = true;
										double thisDist = (sqrt(abs((cix - px1)*(cix - px1) + (ciy - py1)*(ciy - py1) + (ciz - pz1)*(ciz - pz1))));
										if (minDist == -1 || thisDist < minDist)
										{
											collideTriangle = currTriangle;
											collidePosition.x = (float)cix;
											collidePosition.y = (float)ciy;
											collidePosition.z = (float)ciz;
											minDist = thisDist;
											finalModel = cm;
										}
									}
								}
							}
						}
					}

					//determine the next node
					deepestNode = node;
					if (node->depth != treeMaxDepth) //make sure we aren't at a leaf node
					{
						if (px1 < node->xMid)
						{
							if (pz1 < node->zMid)
							{
								node = node->botLeft;
							}
							else
							{
								node = node->topLeft;
							}
						}
						else
						{
							if (pz1 < node->zMid)
							{
								node = node->botRight;
							}
							else
							{
								node = node->topRight;
							}
						}
					}
					else
					{
						node = nullptr;
					}
				}

				node = cm->quadTreeRoot;

				//search for (px2, pz2)
				while (node != nullptr)
				{
					if (std::find(alreadySearchedNodes.begin(), alreadySearchedNodes.end(), node) == alreadySearchedNodes.end())
					{
						alreadySearchedNodes.push_back(node);

						//check through node.tris;
						for (Triangle3D* currTriangle : node->tris)
						{
							//Bounds check on individual triangle
							if (px1 - checkRadius <= currTriangle->maxX && px1 + checkRadius >= currTriangle->minX &&
								pz1 - checkRadius <= currTriangle->maxZ && pz1 + checkRadius >= currTriangle->minZ &&
								py1 - checkRadius <= currTriangle->maxY && py1 + checkRadius >= currTriangle->minY)
							{
								tx1 = currTriangle->p1X;
								tx2 = currTriangle->p2X;
								tx3 = currTriangle->p3X;
								ty1 = currTriangle->p1Y;
								ty2 = currTriangle->p2Y;
								ty3 = currTriangle->p3Y;
								tz1 = currTriangle->p1Z;
								tz2 = currTriangle->p2Z;
								tz3 = currTriangle->p3Z;
								A = currTriangle->A;
								B = currTriangle->B;
								C = currTriangle->C;
								D = currTriangle->D;

								numerator = (A*px1 + B*py1 + C*pz1 + D);
								denominator = (A*(px1 - px2) + B*(py1 - py2) + C*(pz1 - pz2));

								if (denominator != 0)
								{
									u = (numerator / denominator);
									double cix = px1 + u*(px2 - px1);
									double ciy = py1 + u*(py2 - py1);
									double ciz = pz1 + u*(pz2 - pz1);

									if (B != 0)
									{
										double planey1 = (((-A*px1) + (-C*pz1) - D) / B);
										double planey2 = (((-A*px2) + (-C*pz2) - D) / B);
										firstAbove = copysign(1, py1 - planey1);
										secondAbove = copysign(1, py2 - planey2);
									}
									else if (A != 0)
									{
										double planex1 = (((-B*py1) + (-C*pz1) - D) / A);
										double planex2 = (((-B*py2) + (-C*pz2) - D) / A);
										firstAbove = copysign(1, px1 - planex1);
										secondAbove = copysign(1, px2 - planex2);
									}
									else if (C != 0)
									{
										double planez1 = (((-B*py1) + (-A*px1) - D) / C);
										double planez2 = (((-B*py2) + (-A*px2) - D) / C);
										firstAbove = copysign(1, pz1 - planez1);
										secondAbove = copysign(1, pz2 - planez2);
									}

									if (secondAbove != firstAbove &&
										checkPointInTriangle3D(cix, ciy, ciz, tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3,
											abs(currTriangle->normal.x),
											abs(currTriangle->normal.y),
											abs(currTriangle->normal.z)))
									{
										//what is the distance to the triangle? set it to maxdist
										triangleCollide = true;
										double thisDist = (sqrt(abs((cix - px1)*(cix - px1) + (ciy - py1)*(ciy - py1) + (ciz - pz1)*(ciz - pz1))));
										if (minDist == -1 || thisDist < minDist)
										{
											collideTriangle = currTriangle;
											collidePosition.x = (float)cix;
											collidePosition.y = (float)ciy;
											collidePosition.z = (float)ciz;
											minDist = thisDist;
											finalModel = cm;
										}
									}
								}
							}
						}
					}

					//determine the next node
					QuadTreeNode* before = node;
					if (node->depth != treeMaxDepth) //make sure we aren't at a leaf node
					{
						if (px2 < node->xMid)
						{
							if (pz2 < node->zMid)
							{
								node = node->botLeft;
							}
							else
							{
								node = node->topLeft;
							}
						}
						else
						{
							if (pz2 < node->zMid)
							{
								node = node->botRight;
							}
							else
							{
								node = node->topRight;
							}
						}
					}
					else
					{
						node = nullptr;
					}

					if (node == nullptr && before != deepestNode) //we have transitioned to a new node, so lets check catty corner nodes
					{
						node = cm->quadTreeRoot;
						//search for (px1, pz2)
						while (node != nullptr)
						{
							if (std::find(alreadySearchedNodes.begin(), alreadySearchedNodes.end(), node) == alreadySearchedNodes.end())
							{
								alreadySearchedNodes.push_back(node);

								//check through node.tris;
								for (Triangle3D* currTriangle : node->tris)
								{
									//Bounds check on individual triangle
									if (px1 - checkRadius <= currTriangle->maxX && px1 + checkRadius >= currTriangle->minX &&
										pz1 - checkRadius <= currTriangle->maxZ && pz1 + checkRadius >= currTriangle->minZ &&
										py1 - checkRadius <= currTriangle->maxY && py1 + checkRadius >= currTriangle->minY)
									{
										tx1 = currTriangle->p1X;
										tx2 = currTriangle->p2X;
										tx3 = currTriangle->p3X;
										ty1 = currTriangle->p1Y;
										ty2 = currTriangle->p2Y;
										ty3 = currTriangle->p3Y;
										tz1 = currTriangle->p1Z;
										tz2 = currTriangle->p2Z;
										tz3 = currTriangle->p3Z;
										A = currTriangle->A;
										B = currTriangle->B;
										C = currTriangle->C;
										D = currTriangle->D;

										numerator = (A*px1 + B*py1 + C*pz1 + D);
										denominator = (A*(px1 - px2) + B*(py1 - py2) + C*(pz1 - pz2));

										if (denominator != 0)
										{
											u = (numerator / denominator);
											double cix = px1 + u*(px2 - px1);
											double ciy = py1 + u*(py2 - py1);
											double ciz = pz1 + u*(pz2 - pz1);

											if (B != 0)
											{
												double planey1 = (((-A*px1) + (-C*pz1) - D) / B);
												double planey2 = (((-A*px2) + (-C*pz2) - D) / B);
												firstAbove = copysign(1, py1 - planey1);
												secondAbove = copysign(1, py2 - planey2);
											}
											else if (A != 0)
											{
												double planex1 = (((-B*py1) + (-C*pz1) - D) / A);
												double planex2 = (((-B*py2) + (-C*pz2) - D) / A);
												firstAbove = copysign(1, px1 - planex1);
												secondAbove = copysign(1, px2 - planex2);
											}
											else if (C != 0)
											{
												double planez1 = (((-B*py1) + (-A*px1) - D) / C);
												double planez2 = (((-B*py2) + (-A*px2) - D) / C);
												firstAbove = copysign(1, pz1 - planez1);
												secondAbove = copysign(1, pz2 - planez2);
											}

											if (secondAbove != firstAbove &&
												checkPointInTriangle3D(cix, ciy, ciz, tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3,
													abs(currTriangle->normal.x),
													abs(currTriangle->normal.y),
													abs(currTriangle->normal.z)))
											{
												//what is the distance to the triangle? set it to maxdist
												triangleCollide = true;
												double thisDist = (sqrt(abs((cix - px1)*(cix - px1) + (ciy - py1)*(ciy - py1) + (ciz - pz1)*(ciz - pz1))));
												if (minDist == -1 || thisDist < minDist)
												{
													collideTriangle = currTriangle;
													collidePosition.x = (float)cix;
													collidePosition.y = (float)ciy;
													collidePosition.z = (float)ciz;
													minDist = thisDist;
													finalModel = cm;
												}
											}
										}
									}
								}
							}

							//determine the next node
							if (node->depth != treeMaxDepth) //make sure we aren't at a leaf node
							{
								if (px1 < node->xMid)
								{
									if (pz2 < node->zMid)
									{
										node = node->botLeft;
									}
									else
									{
										node = node->topLeft;
									}
								}
								else
								{
									if (pz2 < node->zMid)
									{
										node = node->botRight;
									}
									else
									{
										node = node->topRight;
									}
								}
							}
							else
							{
								node = nullptr;
							}
						}

						node = cm->quadTreeRoot;
						//search for (px2, pz1)
						while (node != nullptr)
						{
							if (std::find(alreadySearchedNodes.begin(), alreadySearchedNodes.end(), node) == alreadySearchedNodes.end())
							{
								alreadySearchedNodes.push_back(node);

								//check through node.tris;
								for (Triangle3D* currTriangle : node->tris)
								{
									//Bounds check on individual triangle
									if (px1 - checkRadius <= currTriangle->maxX && px1 + checkRadius >= currTriangle->minX &&
										pz1 - checkRadius <= currTriangle->maxZ && pz1 + checkRadius >= currTriangle->minZ &&
										py1 - checkRadius <= currTriangle->maxY && py1 + checkRadius >= currTriangle->minY)
									{
										tx1 = currTriangle->p1X;
										tx2 = currTriangle->p2X;
										tx3 = currTriangle->p3X;
										ty1 = currTriangle->p1Y;
										ty2 = currTriangle->p2Y;
										ty3 = currTriangle->p3Y;
										tz1 = currTriangle->p1Z;
										tz2 = currTriangle->p2Z;
										tz3 = currTriangle->p3Z;
										A = currTriangle->A;
										B = currTriangle->B;
										C = currTriangle->C;
										D = currTriangle->D;

										numerator = (A*px1 + B*py1 + C*pz1 + D);
										denominator = (A*(px1 - px2) + B*(py1 - py2) + C*(pz1 - pz2));

										if (denominator != 0)
										{
											u = (numerator / denominator);
											double cix = px1 + u*(px2 - px1);
											double ciy = py1 + u*(py2 - py1);
											double ciz = pz1 + u*(pz2 - pz1);

											if (B != 0)
											{
												double planey1 = (((-A*px1) + (-C*pz1) - D) / B);
												double planey2 = (((-A*px2) + (-C*pz2) - D) / B);
												firstAbove = copysign(1, py1 - planey1);
												secondAbove = copysign(1, py2 - planey2);
											}
											else if (A != 0)
											{
												double planex1 = (((-B*py1) + (-C*pz1) - D) / A);
												double planex2 = (((-B*py2) + (-C*pz2) - D) / A);
												firstAbove = copysign(1, px1 - planex1);
												secondAbove = copysign(1, px2 - planex2);
											}
											else if (C != 0)
											{
												double planez1 = (((-B*py1) + (-A*px1) - D) / C);
												double planez2 = (((-B*py2) + (-A*px2) - D) / C);
												firstAbove = copysign(1, pz1 - planez1);
												secondAbove = copysign(1, pz2 - planez2);
											}

											if (secondAbove != firstAbove &&
												checkPointInTriangle3D(cix, ciy, ciz, tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3,
													abs(currTriangle->normal.x),
													abs(currTriangle->normal.y),
													abs(currTriangle->normal.z)))
											{
												//what is the distance to the triangle? set it to maxdist
												triangleCollide = true;
												double thisDist = (sqrt(abs((cix - px1)*(cix - px1) + (ciy - py1)*(ciy - py1) + (ciz - pz1)*(ciz - pz1))));
												if (minDist == -1 || thisDist < minDist)
												{
													collideTriangle = currTriangle;
													collidePosition.x = (float)cix;
													collidePosition.y = (float)ciy;
													collidePosition.z = (float)ciz;
													minDist = thisDist;
													finalModel = cm;
												}
											}
										}
									}
								}
							}

							//determine the next node
							if (node->depth != treeMaxDepth) //make sure we aren't at a leaf node
							{
								if (px2 < node->xMid)
								{
									if (pz1 < node->zMid)
									{
										node = node->botLeft;
									}
									else
									{
										node = node->topLeft;
									}
								}
								else
								{
									if (pz1 < node->zMid)
									{
										node = node->botRight;
									}
									else
									{
										node = node->topRight;
									}
								}
							}
							else
							{
								node = nullptr;
							}
						}
					}
				}
			}
			else
			{
				for (Triangle3D* currTriangle : cm->triangles)
				{
					//Bounds check on individual triangle
					if (px1 - checkRadius <= currTriangle->maxX && px1 + checkRadius >= currTriangle->minX &&
						pz1 - checkRadius <= currTriangle->maxZ && pz1 + checkRadius >= currTriangle->minZ &&
						py1 - checkRadius <= currTriangle->maxY && py1 + checkRadius >= currTriangle->minY)
					{
						tx1 = currTriangle->p1X;
						tx2 = currTriangle->p2X;
						tx3 = currTriangle->p3X;
						ty1 = currTriangle->p1Y;
						ty2 = currTriangle->p2Y;
						ty3 = currTriangle->p3Y;
						tz1 = currTriangle->p1Z;
						tz2 = currTriangle->p2Z;
						tz3 = currTriangle->p3Z;
						A = currTriangle->A;
						B = currTriangle->B;
						C = currTriangle->C;
						D = currTriangle->D;

						numerator = (A*px1 + B*py1 + C*pz1 + D);
						denominator = (A*(px1 - px2) + B*(py1 - py2) + C*(pz1 - pz2));

						if (denominator != 0)
						{
							u = (numerator / denominator);
							double cix = px1 + u*(px2 - px1);
							double ciy = py1 + u*(py2 - py1);
							double ciz = pz1 + u*(pz2 - pz1);

							if (B != 0)
							{
								double planey1 = (((-A*px1) + (-C*pz1) - D) / B);
								double planey2 = (((-A*px2) + (-C*pz2) - D) / B);
								firstAbove = copysign(1, py1 - planey1);
								secondAbove = copysign(1, py2 - planey2);
							}
							else if (A != 0)
							{
								double planex1 = (((-B*py1) + (-C*pz1) - D) / A);
								double planex2 = (((-B*py2) + (-C*pz2) - D) / A);
								firstAbove = copysign(1, px1 - planex1);
								secondAbove = copysign(1, px2 - planex2);
							}
							else if (C != 0)
							{
								double planez1 = (((-B*py1) + (-A*px1) - D) / C);
								double planez2 = (((-B*py2) + (-A*px2) - D) / C);
								firstAbove = copysign(1, pz1 - planez1);
								secondAbove = copysign(1, pz2 - planez2);
							}

							if (secondAbove != firstAbove &&
								checkPointInTriangle3D(cix, ciy, ciz, tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3,
									abs(currTriangle->normal.x),
									abs(currTriangle->normal.y),
									abs(currTriangle->normal.z)))
							{
								//what is the distance to the triangle? set it to maxdist
								triangleCollide = true;
								double thisDist = (sqrt(abs((cix - px1)*(cix - px1) + (ciy - py1)*(ciy - py1) + (ciz - pz1)*(ciz - pz1))));
								if (minDist == -1 || thisDist < minDist)
								{
									collideTriangle = currTriangle;
									collidePosition.x = (float)cix;
									collidePosition.y = (float)ciy;
									collidePosition.z = (float)ciz;
									minDist = thisDist;
									finalModel = cm;
								}
							}
						}
					}
				}
			}
		}
	}
	//CollisionChecker::collideModels.remove(CollisionChecker::stageCollideModel);

	if (CollisionChecker::checkPlayer && finalModel != nullptr)
	{
		finalModel->playerIsOn = true;
	}
	CollisionChecker::checkPlayer = false;

	return triangleCollide;
}

bool CollisionChecker::checkPointInTriangle3D(
	double checkx, double checky, double checkz,
	double cx1, double cy1, double cz1,
	double cx2, double cy2, double cz2,
	double cx3, double cy3, double cz3,
	double nX, double nY, double nZ)
{
	if (nY > nX && nY > nZ)
	{
		//from the top
		return (checkPointInTriangle2D(checkx, checkz, cx1, cz1, cx2, cz2, cx3, cz3));
	}
	else if (nX > nZ)
	{
		//from the left
		return (checkPointInTriangle2D(checkz, checky, cz1, cy1, cz2, cy2, cz3, cy3));
	}

	//from the front
	return (checkPointInTriangle2D(checkx, checky, cx1, cy1, cx2, cy2, cx3, cy3));
}

bool CollisionChecker::checkPointInTriangle2D(
	double x, double y,
	double x1, double y1,
	double x2, double y2,
	double x3, double y3)
{
	double denominator = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
	double a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / denominator;
	double b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / denominator;
	double c = 1 - a - b;

	return (0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1);
}


void CollisionChecker::deleteAllCollideModels()
{
	while (CollisionChecker::collideModels.size() > 0)
	{
		CollisionModel* cm = CollisionChecker::collideModels.front();
		CollisionChecker::collideModels.remove(cm);
		cm->deleteMe();
		delete cm;
		INCR_DEL
	}
}

void CollisionChecker::deleteAllCollideModelsExceptQuadTrees()
{
	std::list<CollisionModel*> modelsToDelete;

	for (CollisionModel* cm : CollisionChecker::collideModels)
	{
		if (cm->hasQuadTree() == false)
		{
			modelsToDelete.push_back(cm);
		}
	}

	for (CollisionModel* cm : modelsToDelete)
	{
		CollisionChecker::collideModels.remove(cm);
		cm->deleteMe();
		delete cm;
		INCR_DEL
	}
}

/*
void CollisionChecker::deleteStageCollideModel()
{
	if (CollisionChecker::stageCollideModel != nullptr)
	{
		CollisionChecker::stageCollideModel->deleteAllTriangles();
		delete CollisionChecker::stageCollideModel;
		CollisionChecker::stageCollideModel = nullptr;
		INCR_DEL
	}
	else
	{
		std::fprintf(stdout, "tried to delete null stage collision model\n");
	}
}
*/

void CollisionChecker::deleteCollideModel(CollisionModel* cm)
{
	CollisionChecker::collideModels.remove(cm);
	cm->deleteMe();
	delete cm;
	INCR_DEL
}

//The model added must be created with the new keyword, as it will be deleted
// here later, via deleteCollideModel or deleteAlmostAllCollideModels call
void CollisionChecker::addCollideModel(CollisionModel* cm)
{
	CollisionChecker::collideModels.push_back(cm);
}


Triangle3D* CollisionChecker::getCollideTriangle()
{
	return CollisionChecker::collideTriangle;
}


Vector3f* CollisionChecker::getCollidePosition()
{
	return &CollisionChecker::collidePosition;
}
