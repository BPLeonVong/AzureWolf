/*

	Copyright 2010 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "AzureWolfStd.h"

#include "camera.h"

const static float StepScale = 0.001f;

Camera::Camera()
{
    m_pos    = Vector3f(0.0f, 0.0f, 0.0f);
    m_target = Vector3f(0.0f, 0.0f, 1.0f);
    m_up     = Vector3f(0.0f, 1.0f, 0.0f);
}


Camera::Camera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    m_pos    = Pos;
    m_target = Target;
    m_target.Normalize();
    m_up     = Up;
    m_up.Normalize();
}

void Camera::MoveUp()
{
	m_pos += (m_target * StepScale);
}
void Camera::MoveRight()
{
	Vector3f Right = m_up.Cross(m_target);
	Right.Normalize();
	Right *= StepScale;
	m_pos += Right;
}
void Camera::MoveDown()
{
	m_pos -= (m_target * StepScale);
}
void Camera::MoveLeft()
{
	Vector3f Left = m_target.Cross(m_up);
	Left.Normalize();
	Left *= StepScale;
	m_pos += Left;
}