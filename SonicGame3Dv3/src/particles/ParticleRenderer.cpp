#include <list>
#include <unordered_map>
#include <glad/glad.h>

#include "../renderEngine/renderEngine.h"
#include "../toolbox/matrix.h"
#include "../models/models.h"
#include "particleshader.h"
#include "../toolbox/vector.h"
#include "particle.h"
#include "particletexture.h"
#include "particlerenderer.h"
#include "../toolbox/maths.h"
#include "../entities/camera.h"
#include "../engineTester/main.h"


ParticleRenderer::ParticleRenderer(Matrix4f* projectionMatrix)
{
	std::vector<float> vertices;
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);

	quad = new RawModel(Loader_loadToVAO(&vertices, 2)); Global::countNew++;
	shader = new ParticleShader(); Global::countNew++;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void ParticleRenderer::render(std::unordered_map<ParticleTexture*, std::list<Particle*>>* particles, Camera* camera, float brightness, int clipSide)
{
	Matrix4f viewMatrix;
	createViewMatrix(&viewMatrix, camera);
	prepare();
	shader->loadBrightness(brightness);

	switch (clipSide + 1)
	{
		case 0: //side -1
			for (auto texture : (*particles))
			{
				//bind texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture.first->getTextureID());
				shader->loadOpacity(texture.first->getOpacity());
				shader->loadGlow(texture.first->getGlow());
				std::list<Particle*>* texturesList = &texture.second;
				for (Particle* particle : (*texturesList))
				{
					if (particle->getPosition()->y < 0)
					{
						updateModelViewMatrix(particle->getPosition(), particle->getRotation(), particle->getScale(), &viewMatrix);
						shader->loadTextureCoordInfo(particle->getTexOffset1(), particle->getTexOffset2(), (float)texture.first->getNumberOfRows(), particle->getBlend());
						glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
					}
				}
			}
			break;

		case 1: //side 0
			for (auto texture : (*particles))
			{
				//bind texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture.first->getTextureID());
				shader->loadOpacity(texture.first->getOpacity());
				shader->loadGlow(texture.first->getGlow());

				//fprintf(stdout, "texID  %d\n", texture.first->getTextureID());
				//fprintf(stdout, "opa    %f\n", texture.first->getOpacity());
				//fprintf(stdout, "glow   %f\n", texture.first->getGlow());

				std::list<Particle*>* texturesList = &texture.second;
				for (Particle* particle : (*texturesList))
				{
					//fprintf(stdout, "pos  %f %f %f\n", particle->getPosition()->x, particle->getPosition()->y, particle->getPosition()->z);
					//fprintf(stdout, "rot  %f\n", particle->getRotation());
					//fprintf(stdout, "sca  %f\n", particle->getScale());
					//fprintf(stdout, "tex1 %f %f\n", particle->getTexOffset1()->getX(), particle->getTexOffset1()->getY());
					//fprintf(stdout, "tex2 %f %f\n", particle->getTexOffset2()->getX(), particle->getTexOffset2()->getY());
					//fprintf(stdout, "rows %f\n", (float)texture.first->getNumberOfRows());
					//fprintf(stdout, "ble  %f\n\n", particle->getBlend());
					updateModelViewMatrix(particle->getPosition(), particle->getRotation(), particle->getScale(), &viewMatrix);
					shader->loadTextureCoordInfo(particle->getTexOffset1(), particle->getTexOffset2(), (float)texture.first->getNumberOfRows(), particle->getBlend());
					glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
				}
			}
			break;

		case 2: //side 1
			for (auto texture : (*particles))
			{
				//bind texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture.first->getTextureID());
				shader->loadOpacity(texture.first->getOpacity());
				shader->loadGlow(texture.first->getGlow());
				std::list<Particle*>* texturesList = &texture.second;
				for (Particle* particle : (*texturesList))
				{
					if (particle->getPosition()->y >= 0)
					{
						updateModelViewMatrix(particle->getPosition(), particle->getRotation(), particle->getScale(), &viewMatrix);
						shader->loadTextureCoordInfo(particle->getTexOffset1(), particle->getTexOffset2(), (float)texture.first->getNumberOfRows(), particle->getBlend());
						glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
					}
				}
			}
			break;

		default:
			break;
	}

	finishRendering();
}

void ParticleRenderer::cleanUp()
{
	shader->cleanUp();
}

void ParticleRenderer::updateModelViewMatrix(Vector3f* position, float rotation, float scale, Matrix4f* viewMatrix)
{
	Matrix4f modelMatrix;
	modelMatrix.setIdentity();
	modelMatrix.translate(position);
	modelMatrix.m00 = viewMatrix->m00;
	modelMatrix.m01 = viewMatrix->m10;
	modelMatrix.m02 = viewMatrix->m20;
	modelMatrix.m10 = viewMatrix->m01;
	modelMatrix.m11 = viewMatrix->m11;
	modelMatrix.m12 = viewMatrix->m21;
	modelMatrix.m20 = viewMatrix->m02;
	modelMatrix.m21 = viewMatrix->m12;
	modelMatrix.m22 = viewMatrix->m22;
	Vector3f axis(0, 0, 1);
	modelMatrix.rotate(toRadians(rotation), &axis);
	Vector3f scaleVec(scale, scale, scale);
	modelMatrix.scale(&scaleVec);
	Matrix4f modelViewMatrix = Matrix4f(modelMatrix);
	viewMatrix->multiply(&modelViewMatrix, &modelViewMatrix);
	shader->loadModelViewMatrix(&modelViewMatrix);
}

void ParticleRenderer::updateProjectionMatrix(Matrix4f* projectionMatrix)
{
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void ParticleRenderer::prepare()
{
	shader->start();
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);
}

void ParticleRenderer::finishRendering()
{
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}
