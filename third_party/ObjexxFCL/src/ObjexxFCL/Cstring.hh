#ifndef ObjexxFCL_Cstring_hh_INCLUDED
#define ObjexxFCL_Cstring_hh_INCLUDED

// Cstring: C String Wrapper
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2014 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// C++ Headers
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <string>
#include <utility>

namespace ObjexxFCL {

// Types
typedef  char       *    cstring;
typedef  char const *  c_cstring;

// Cstring: C String Wrapper
//
// Note:
//  A memory-managed C string (char*) wrapper for convenience when using a C-style interfaces
//  Explicit conversion from std::string
//  Implicit conversion from/to char* for argument passing
//  Automatic memory management
//  Invariant: Null-terminated upon return from any constructor or function
class Cstring
{

public: // Types

	// STL Style
	typedef  std::size_t  size_type;

	// C++ Style
	typedef  std::size_t  Size;

public: // Creation

	// Default Constructor
	inline
	Cstring() :
		str_( new char[ 1 ] )
	{
		str_[ 0 ] = '\0';
	}

	// Copy Constructor
	inline
	Cstring( Cstring const & s ) :
		str_( new char[ std::strlen( s.str_ ) + 1 ] )
	{
		std::memcpy( str_, s.str_, std::strlen( s.str_ ) + 1 );
	}

	// C string Constructor: Implicit Conversion
	inline
	Cstring( c_cstring const s ) :
		str_( new char[ std::strlen( s ) + 1 ] )
	{
		std::memcpy( str_, s, std::strlen( s ) + 1 );
	}

	// std::string Constructor
	inline
	explicit
	Cstring( std::string const & s ) :
		str_( new char[ s.length() + 1 ] )
	{
		size_type const len( s.length() );
		s.copy( str_, len );
		str_[ len ] = '\0';
	}

	// Cstring + Length Constructor
	inline
	Cstring(
		Cstring const & s,
		size_type const len
	) :
		str_( new char[ len + 1 ] )
	{
		assert( len <= s.length() );
		std::memcpy( str_, s.str_, len );
		str_[ len ] = '\0';
	}

	// C string + Length Constructor
	inline
	Cstring(
		c_cstring const s,
		size_type const len
	) :
		str_( new char[ len + 1 ] )
	{
		assert( len <= std::strlen( s ) );
		std::memcpy( str_, s, len );
		str_[ len ] = '\0';
	}

	// std::string + Length Constructor
	inline
	Cstring(
		std::string const & s,
		size_type const len
	) :
		str_( new char[ len + 1 ] )
	{
		assert( len <= s.length() );
		s.copy( str_, len );
		str_[ len ] = '\0';
	}

	// char Constructor
	inline
	explicit
	Cstring( char const c ) :
		str_( new char[ 2 ] )
	{
		str_[ 0 ] = c;
		str_[ 1 ] = '\0';
	}

	// Length Constructor
	inline
	explicit
	Cstring( size_type const len ) :
		str_( new char[ len + 1 ] )
	{
		std::memset( str_, ' ', len );
		str_[ len ] = '\0';
	}

	// Length Constructor
	inline
	explicit
	Cstring( int const len ) :
		str_( new char[ len + 1 ] )
	{
		std::memset( str_, ' ', len );
		str_[ len ] = '\0';
	}

	// Destructor
	inline
	virtual
	~Cstring()
	{
		delete[] str_;
	}

public: // Conversion

	// C string Conversion: Invalid after str_ is reallocated
	inline
	operator c_cstring() const
	{
		return str_;
	}

	// C string Conversion: Invalid after str_ is reallocated
	inline
	operator cstring()
	{
		return str_;
	}

public: // Assignment

	// Copy Assignment
	inline
	Cstring &
	operator =( Cstring const & s )
	{
		if ( this != &s ) {
			size_type const len( s.length() + 1 );
			delete[] str_; str_ = new char[ len ];
			std::memcpy( str_, s.str_, len );
		}
		return *this;
	}

	// cstring Assignment
	inline
	Cstring &
	operator =( c_cstring const s )
	{
		size_type const len( std::strlen( s ) + 1 );
		delete[] str_; str_ = new char[ len ];
		std::memmove( str_, s, len );
		return *this;
	}

	// std::string Assignment
	inline
	Cstring &
	operator =( std::string const & s )
	{
		size_type const len( s.length() );
		delete[] str_; str_ = new char[ len + 1 ];
		s.copy( str_, len );
		str_[ len ] = '\0';
		return *this;
	}

	// char Assignment
	inline
	Cstring &
	operator =( char const c )
	{
		delete[] str_; str_ = new char[ 2 ];
		str_[ 0 ] = c;
		str_[ 1 ] = '\0';
		return *this;
	}

	// Cstring Append
	inline
	Cstring &
	operator +=( Cstring const & s )
	{
		Cstring( *this + s ).swap( *this );
		return *this;
	}

	// cstring Append
	inline
	Cstring &
	operator +=( c_cstring const s )
	{
		Cstring( *this + s ).swap( *this );
		return *this;
	}

	// std::string Append
	inline
	Cstring &
	operator +=( std::string const & s )
	{
		Cstring( *this + s ).swap( *this );
		return *this;
	}

	// char Append
	inline
	Cstring &
	operator +=( char const c )
	{
		Cstring( *this + c ).swap( *this );
		return *this;
	}

public: // Predicate

	// Empty?
	inline
	bool
	empty() const
	{
		return ( std::strlen( str_ ) == 0 );
	}

	// Blank?
	inline
	bool
	is_blank() const
	{
		return ( len_trim() == 0 );
	}

	// Not blank?
	inline
	bool
	not_blank() const
	{
		return ( len_trim() != 0 );
	}

	// Has any Character of a Cstring?
	bool
	has_any_of( Cstring const & s ) const;

	// Has any Character of a cstring?
	bool
	has_any_of( c_cstring const s ) const;

	// Has any Character of a std::string?
	bool
	has_any_of( std::string const s ) const;

	// Has a Character?
	bool
	has_any_of( char const c ) const;

	// Has a Character?
	bool
	has( char const c ) const;

public: // Inspector

	// Length
	inline
	size_type
	length() const
	{
		return std::strlen( str_ );
	}

	// Length
	inline
	size_type
	len() const
	{
		return std::strlen( str_ );
	}

	// Size
	inline
	size_type
	size() const
	{
		return std::strlen( str_ );
	}

	// Length Space-Trimmed
	size_type
	len_trim() const;

	// Length Whitespace-Trimmed
	size_type
	len_trim_whitespace() const;

	// Find First Occurrence of a Character
	size_type
	find( char const c ) const;

	// Find Last Occurrence of a Character
	size_type
	find_last( char const c ) const;

public: // Modifier

	// Lowercase
	Cstring &
	lowercase();

	// Uppercase
	Cstring &
	uppercase();

	// Left Justify
	Cstring &
	left_justify();

	// Right Justify
	Cstring &
	right_justify();

	// Trim Trailing Space
	inline
	Cstring &
	trim()
	{
		str_[ len_trim() ] = '\0';
		return *this;
	}

	// Trim Trailing Whitespace
	inline
	Cstring &
	trim_whitespace()
	{
		str_[ len_trim_whitespace() ] = '\0';
		return *this;
	}

	// Center
	Cstring &
	center();

	// Compress Out Whitespace
	Cstring &
	compress();

	// swap( Cstring )
	inline
	void
	swap( Cstring & s )
	{
		std::swap( str_, s.str_ );
	}

	// swap( Cstring, Cstring )
	inline
	friend
	void
	swap( Cstring & s, Cstring & t )
	{
		std::swap( s.str_, t.str_ );
	}

public: // Subscript

	// Cstring[ i ] const
	inline
	char
	operator []( size_type const i ) const
	{
		assert( i < std::strlen( str_ ) );
		return str_[ i ];
	}

	// Cstring[ i ]
	inline
	char &
	operator []( size_type const i )
	{
		assert( i < std::strlen( str_ ) );
		return str_[ i ];
	}

	// Cstring[ i ] const
	//  Overload prevents ambiguity with built-in operator[] with int arguments
	inline
	char
	operator []( int const i ) const
	{
		assert( i >= 0 );
		assert( static_cast< size_type >( i ) < std::strlen( str_ ) );
		return str_[ i ];
	}

	// Cstring[ i ]
	//  Overload prevents ambiguity with built-in operator[] with int arguments
	inline
	char &
	operator []( int const i )
	{
		assert( i >= 0 );
		assert( static_cast< size_type >( i ) < std::strlen( str_ ) );
		return str_[ i ];
	}

public: // Concatenation

	// Cstring + Cstring
	inline
	friend
	Cstring
	operator +( Cstring const & s, Cstring const & t )
	{
		size_type const s_len( s.length() );
		size_type const t_len( t.length() );
		Cstring u( s_len + t_len );
		std::memcpy( u.str_, s.str_, s_len );
		std::memcpy( u.str_ + s_len, t.str_, t_len + 1 );
		return u;
	}

	// Cstring + cstring
	inline
	friend
	Cstring
	operator +( Cstring const & s, c_cstring const t )
	{
		size_type const s_len( s.length() );
		size_type const t_len( std::strlen( t ) );
		Cstring u( s_len + t_len );
		std::memcpy( u.str_, s.str_, s_len );
		std::memcpy( u.str_ + s_len, t, t_len + 1 );
		return u;
	}

	// cstring + Cstring
	inline
	friend
	Cstring
	operator +( c_cstring const s, Cstring const & t )
	{
		size_type const s_len( std::strlen( s ) );
		size_type const t_len( t.length() );
		Cstring u( s_len + t_len );
		std::memcpy( u.str_, s, s_len );
		std::memcpy( u.str_ + s_len, t.str_, t_len + 1 );
		return u;
	}

	// Cstring + std::string
	inline
	friend
	Cstring
	operator +( Cstring const & s, std::string const & t )
	{
		size_type const s_len( s.length() );
		size_type const t_len( t.length() );
		Cstring u( s_len + t_len );
		std::memcpy( u.str_, s.str_, s_len );
		t.copy( u.str_ + s_len, t_len );
		return u;
	}

	// Cstring + char
	inline
	friend
	Cstring
	operator +( Cstring const & s, char const c )
	{
		size_type const s_len( s.length() );
		Cstring u( s_len + 1 );
		std::memcpy( u.str_, s.str_, s_len );
		u.str_[ s_len ] = c;
		return u;
	}

	// char + Cstring
	inline
	friend
	Cstring
	operator +( char const c, Cstring const & t )
	{
		size_type const t_len( t.length() );
		Cstring u( 1 + t_len );
		u.str_[ 0 ] = c;
		std::memcpy( u.str_ + 1, t.str_, t_len + 1 );
		return u;
	}

public: // Generator

	// Lowercased Copy
	inline
	Cstring
	lowercased() const
	{
		return Cstring( *this ).lowercase();
	}

	// Uppercased Copy
	inline
	Cstring
	uppercased() const
	{
		return Cstring( *this ).uppercase();
	}

	// Left-Justified Copy
	inline
	Cstring
	left_justified() const
	{
		return Cstring( *this ).left_justify();
	}

	// Right-Justified Copy
	inline
	Cstring
	right_justified() const
	{
		return Cstring( *this ).right_justify();
	}

	// Space-Trimmed Copy
	inline
	Cstring
	trimmed() const
	{
		return Cstring( *this, len_trim() );
	}

	// Whitespace-Trimmed Copy
	inline
	Cstring
	trimmed_whitespace() const
	{
		return Cstring( *this, len_trim_whitespace() );
	}

	// Centered Copy
	inline
	Cstring
	centered() const
	{
		return Cstring( *this ).center();
	}

	// Compressed Copy
	inline
	Cstring
	compressed() const
	{
		return Cstring( *this ).compress();
	}

public: // Comparison

	// Cstring == Cstring
	inline
	friend
	bool
	operator ==( Cstring const & s, Cstring const & t )
	{
		return ( std::strcmp( s.str_, t.str_ ) == 0 );
	}

	// Cstring != Cstring
	inline
	friend
	bool
	operator !=( Cstring const & s, Cstring const & t )
	{
		return ( std::strcmp( s.str_, t.str_ ) != 0 );
	}

	// Cstring == cstring
	inline
	friend
	bool
	operator ==( Cstring const & s, c_cstring const t )
	{
		return ( std::strcmp( s.str_, t ) == 0 );
	}

	// cstring == Cstring
	inline
	friend
	bool
	operator ==( c_cstring const t, Cstring const & s )
	{
		return ( std::strcmp( s.str_, t ) == 0 );
	}

	// Cstring != cstring
	inline
	friend
	bool
	operator !=( Cstring const & s, c_cstring const t )
	{
		return ( std::strcmp( s.str_, t ) != 0 );
	}

	// cstring != Cstring
	inline
	friend
	bool
	operator !=( c_cstring const t, Cstring const & s )
	{
		return ( std::strcmp( s.str_, t ) != 0 );
	}

	// Cstring == std::string
	inline
	friend
	bool
	operator ==( Cstring const & s, std::string const & t )
	{
		return ( s.str_ == t );
	}

	// std::string == Cstring
	inline
	friend
	bool
	operator ==( std::string const & t, Cstring const & s )
	{
		return ( t == s.str_ );
	}

	// Cstring != std::string
	inline
	friend
	bool
	operator !=( Cstring const & s, std::string const & t )
	{
		return ( s.str_ != t );
	}

	// std::string != Cstring
	inline
	friend
	bool
	operator !=( std::string const & t, Cstring const & s )
	{
		return ( t != s.str_ );
	}

	// Cstring == char
	inline
	friend
	bool
	operator ==( Cstring const & s, char const c )
	{
		return ( ( s.length() == 1 ) && ( s.str_[ 0 ] == c ) );
	}

	// char == Cstring
	inline
	friend
	bool
	operator ==( char const c, Cstring const & s )
	{
		return ( ( s.length() == 1 ) && ( s.str_[ 0 ] == c ) );
	}

	// Cstring != char
	inline
	friend
	bool
	operator !=( Cstring const & s, char const c )
	{
		return ( ( s.length() != 1 ) || ( s.str_[ 0 ] != c ) );
	}

	// char != Cstring
	inline
	friend
	bool
	operator !=( char const c, Cstring const & s )
	{
		return ( ( s.length() != 1 ) || ( s.str_[ 0 ] != c ) );
	}

	// Cstring == Cstring Case-Insensitively?
	friend
	bool
	equali( Cstring const & s, Cstring const & t );

	// Cstring == cstring Case-Insensitively?
	friend
	bool
	equali( Cstring const & s, c_cstring const t );

	// cstring == Cstring Case-Insensitively?
	friend
	bool
	equali( c_cstring const s, Cstring const & t );

	// Cstring == std::string Case-Insensitively?
	friend
	bool
	equali( Cstring const & s, std::string const & t );

	// std::string == Cstring Case-Insensitively?
	friend
	bool
	equali( std::string const & s, Cstring const & t );

	// Cstring == char Case-Insensitively?
	friend
	bool
	equali( Cstring const & s, char const c );

	// char == Cstring Case-Insensitively?
	friend
	bool
	equali( char const c, Cstring const & s );

public: // I/O

	// Output to Stream
	friend
	std::ostream &
	operator <<( std::ostream & stream, Cstring const & s );

	// Input from Stream
	friend
	std::istream &
	operator >>( std::istream & stream, Cstring & s );

public: // Data

	static size_type const npos = static_cast< size_type >( -1 ); // Unbounded "size"

private: // Data

	char * str_; // String

}; // Cstring

// swap( Cstring, Cstring );
void
swap( Cstring & s, Cstring & t );

// Cstring + Cstring
Cstring
operator +( Cstring const & s, Cstring const & t );

// Cstring + cstring
Cstring
operator +( Cstring const & s, c_cstring const t );

// cstring + Cstring
Cstring
operator +( c_cstring const s, Cstring const & t );

// Cstring + std::string
Cstring
operator +( Cstring const & s, std::string const & t );

// Cstring + char
Cstring
operator +( Cstring const & s, char const c );

// char + Cstring
Cstring
operator +( char const c, Cstring const & t );

// Cstring == Cstring
bool
operator ==( Cstring const & s, Cstring const & t );

// Cstring != Cstring
bool
operator !=( Cstring const & s, Cstring const & t );

// Cstring == cstring
bool
operator ==( Cstring const & s, c_cstring const t );

// cstring == Cstring
bool
operator ==( c_cstring const t, Cstring const & s );

// Cstring != cstring
bool
operator !=( Cstring const & s, c_cstring const t );

// cstring != Cstring
bool
operator !=( c_cstring const t, Cstring const & s );

// Cstring == std::string
bool
operator ==( Cstring const & s, std::string const & t );

// std::string == Cstring
bool
operator ==( std::string const & t, Cstring const & s );

// Cstring != std::string
bool
operator !=( Cstring const & s, std::string const & t );

// std::string != Cstring
bool
operator !=( std::string const & t, Cstring const & s );

// Cstring == char
bool
operator ==( Cstring const & s, char const c );

// char == Cstring
bool
operator ==( char const c, Cstring const & s );

// Cstring != char
bool
operator !=( Cstring const & s, char const c );

// char != Cstring
bool
operator !=( char const c, Cstring const & s );

// Cstring == Cstring Case-Insensitively?
bool
equali( Cstring const & s, Cstring const & t );

// Cstring == cstring Case-Insensitively?
bool
equali( Cstring const & s, c_cstring const t );

// cstring == Cstring Case-Insensitively?
bool
equali( c_cstring const s, Cstring const & t );

// Cstring == std::string Case-Insensitively?
bool
equali( Cstring const & s, std::string const & t );

// std::string == Cstring Case-Insensitively?
bool
equali( std::string const & s, Cstring const & t );

// Cstring == char Case-Insensitively?
bool
equali( Cstring const & s, char const c );

// char == Cstring Case-Insensitively?
bool
equali( char const c, Cstring const & s );

// Output to Stream
std::ostream &
operator <<( std::ostream & stream, Cstring const & s );

// Input from Stream
std::istream &
operator >>( std::istream & stream, Cstring & s );

} // ObjexxFCL

#endif // ObjexxFCL_Cstring_hh_INCLUDED
