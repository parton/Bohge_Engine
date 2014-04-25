//////////////////////////////////////////////////////////////////////////////////////
//
//						The Bohge Engine License (BEL)
//
//	Copyright (c) 2011-2014 Peng Zhao
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in 
//	all copies or substantial portions of the Software. And the logo of 
//	Bohge Engine shall be displayed full screen for more than 3 seconds 
//	when the software is started. Copyright holders are allowed to develop 
//	game edit based on Bohge Engine, The edit must be released under the MIT 
//	open source license if it is going to be published. In no event shall 
//	copyright holders be prohibited from using any code of Bohge Engine 
//	to develop any other analogous game engines.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////
//	3DMath的拆分实现，请不要单独引用该头文件	//
//////////////////////////////////////////////
#ifndef VECTOR4
#define VECTOR4
#else
#error( "Do not include this file in other files" )
#endif



namespace BohgeEngine
{
	template<typename T>
	class vector4
	{
	public:
		typedef T value_type;
	public:
		union
		{
			struct	{ T	m_x, m_y, m_z, m_w; };
			struct	{ T	m_r, m_g, m_b, m_a; };
			T	data[4];
		};
	private:
		/*此处有可能传进来的是自己，所以最后复制，应为如果提前复制会改变他的计算结果，重要！！！！*/
		BOHGE_FORCEINLINE void _Multiplication(const Matrix44<T>& m44, T& x, T& y, T& z, T& w) const
		{
			T newx = data[0]*m44.data[0]+data[1]*m44.data[4]+data[2]*m44.data[8]+data[3]*m44.data[12];
			T newy = data[0]*m44.data[1]+data[1]*m44.data[5]+data[2]*m44.data[9]+data[3]*m44.data[13];
			T newz = data[0]*m44.data[2]+data[1]*m44.data[6]+data[2]*m44.data[10]+data[3]*m44.data[14];
			T neww = data[0]*m44.data[3]+data[1]*m44.data[7]+data[2]*m44.data[11]+data[3]*m44.data[15];
			x = newx;
			y = newy;
			z = newz;
			w = neww;
		}
	public:
		BOHGE_FORCEINLINE vector4():m_x(0),
			m_y(0),
			m_z(0),
			m_w(0)
		{
		}
		BOHGE_FORCEINLINE vector4(T x, T y, T z, T w = 1.0)
			:m_x(x),
			m_y(y),
			m_z(z),
			m_w(w)
		{
		}
		BOHGE_FORCEINLINE vector4(const vector4& input)
			:m_x(input.m_x),
			m_y(input.m_y),
			m_z(input.m_z),
			m_w(input.m_w)
		{
		}
		explicit BOHGE_FORCEINLINE vector4(const vector3<T>& input)
			:m_x(input.m_x),
			m_y(input.m_y),
			m_z(input.m_z),
			m_w(1.0)
		{
		}
	public:
		BOHGE_FORCEINLINE T Length() const
		{
			return Math::Sqrt( m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w );
		}
		BOHGE_FORCEINLINE T LengthPow() const
		{
			return m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
		}
		BOHGE_FORCEINLINE vector4& NormalizeSelf()
		{
			Math::Normalize( *this, *this );
			return *this;
		}
		//矩阵
		BOHGE_FORCEINLINE vector4 operator* (const Matrix44<T>& m44 ) const
		{
			T x;
			T y;
			T z;
			T w;

			_Multiplication(m44,x,y,z,w);

			return vector4(x,y,z,w);
		}
		BOHGE_FORCEINLINE vector4& operator*= (const Matrix44<T>& m44 )
		{
			_Multiplication( m44, data[0], data[1], data[2], data[3]);
			return *this;
		}
		BOHGE_FORCEINLINE vector4 operator* (const Quaternion<T>& rhs ) const
		{
			vector3<T> temp = vector3<T>( *this );
			temp = Math::Transform_Quat( temp, rhs );
			return vector4( temp.m_x * this->m_w, temp.m_y * this->m_w, temp.m_z * this->m_w, this->m_w );
		}
		BOHGE_FORCEINLINE vector4& operator*= (const Quaternion<T>& rhs )
		{
			vector3<T> temp = vector3<T>( *this );
			temp = Math::Transform_Quat( temp, rhs );
			*this =  vector4( temp.m_x * this->m_w, temp.m_y * this->m_w, temp.m_z * this->m_w, this->m_w );
			return *this;
		}
		//等于
		vector4& operator= (const vector4& input )
		{
			data[0] = input.data[0];
			data[1] = input.data[1];
			data[2] = input.data[2];
			data[3] = input.data[3];
			return *this;
		}
		//vector4
		BOHGE_FORCEINLINE vector4 operator+ (const vector4& input ) const
		{
			return vector4(m_x + input.m_x, m_y + input.m_y, m_z + input.m_z, m_w + input.m_w );
		}
		BOHGE_FORCEINLINE vector4 operator- (const vector4& input ) const
		{
			return vector4(m_x - input.m_x, m_y - input.m_y, m_z - input.m_z, m_w - input.m_w );
		}
		BOHGE_FORCEINLINE vector4 operator* (const vector4& input ) const
		{
			return vector4(m_x * input.m_x, m_y * input.m_y, m_z * input.m_z, m_w * input.m_w );
		}
		BOHGE_FORCEINLINE vector4 operator/ (const vector4& input ) const
		{
			return vector4(m_x / input.m_x, m_y / input.m_y, m_z / input.m_z, m_w / input.m_w );
		}
		BOHGE_FORCEINLINE vector4& operator-= ( const vector4& input )
		{
			m_x -= input.m_x;
			m_y -= input.m_y;
			m_z -= input.m_z;
			m_w -= input.m_w;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator+= ( const vector4& input )
		{
			m_x += input.m_x;
			m_y += input.m_y;
			m_z += input.m_z;
			m_w += input.m_w;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator*= ( const vector4& input )
		{
			m_x *= input.m_x;
			m_y *= input.m_y;
			m_z *= input.m_z;
			m_w *= input.m_w;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator/= ( const vector4& input )
		{
			m_x /= input.m_x;
			m_y /= input.m_y;
			m_z /= input.m_z;
			m_w /= input.m_w;
			return *this;
		}
		//单个数字
		friend BOHGE_FORCEINLINE vector4<T> operator* ( T input, const vector4<T>& rhs )
		{
			return vector4<T>(rhs.m_x * input, rhs.m_y * input, rhs.m_z * input, rhs.m_w * input);
		}
		friend BOHGE_FORCEINLINE vector4<T> operator* ( const vector4<T>& rhs, T input )
		{
			return vector4<T>(rhs.m_x * input, rhs.m_y * input, rhs.m_z * input, rhs.m_w * input);
		}
		BOHGE_FORCEINLINE vector4 operator/ ( T input ) const
		{
			T inv = T(1) / input;
			return vector4(m_x * inv, m_y * inv, m_z * inv, m_w * inv);
		}
		BOHGE_FORCEINLINE vector4 operator+ ( T input ) const
		{
			return vector4(m_x + input, m_y + input, m_z + input, m_w + input);
		}
		BOHGE_FORCEINLINE vector4 operator- ( T input ) const
		{
			return vector4(m_x - input, m_y - input, m_z - input, m_w - input);
		}
		BOHGE_FORCEINLINE vector4& operator*= ( T input )
		{
			m_x *= input;
			m_y *= input;
			m_z *= input;
			m_w *= input;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator/= ( T input )
		{
			T inv = T(1) / input;
			m_x *= inv;
			m_y *= inv;
			m_z *= inv;
			m_w *= inv;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator+= ( T input )
		{
			m_x += input;
			m_y += input;
			m_z += input;
			m_w += input;
			return *this;
		}
		BOHGE_FORCEINLINE vector4& operator-= ( T input )
		{
			m_x -= input;
			m_y -= input;
			m_z -= input;
			m_w -= input;
			return *this;
		}
		//逻辑
		BOHGE_FORCEINLINE bool operator == (const vector4& rhs ) const
		{
			return ( Math::isEqual( m_x, rhs.m_x) ) & ( Math::isEqual( m_y, rhs.m_y) ) & ( Math::isEqual( m_z, rhs.m_z) ) & ( Math::isEqual( m_w, rhs.m_w) );
		}
		BOHGE_FORCEINLINE bool operator != (const vector4& rhs ) const
		{
			return !( *this == rhs );
		}
		//取值
		BOHGE_FORCEINLINE T& operator[] ( int i )
		{
			return data[i];
		}
	public:
		BOHGE_FORCEINLINE void RotateByVector (const vector3<T>& vector , const T radian)
		{
			*this *= Matrix44<T>::CreateRotateMatrix(vector,radian);
		}
		BOHGE_FORCEINLINE void MoveByDirect( const vector3<T>& vector, const T distance)
		{
			*this *= Matrix44<T>::CreateMoveMatrix(vector, distance);
		}
	public:
		BOHGE_FORCEINLINE const T* GetVectorArray() const
		{
			return data;
		}
		static uint Size()
		{
			return 4;
		}
		static uint BitSize()
		{
			return 4 * sizeof(T);
		}
	};
}