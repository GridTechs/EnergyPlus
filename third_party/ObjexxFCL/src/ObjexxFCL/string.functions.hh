#ifndef ObjexxFCL_string_functions_hh_INCLUDED
#define ObjexxFCL_string_functions_hh_INCLUDED

// String Functions
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

// ObjexxFCL Headers
#include <ObjexxFCL/TypeTraits.hh>
#include <ObjexxFCL/char.functions.hh>

// C++ Headers
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

namespace ObjexxFCL {

// Types
typedef  char       *    cstring;
typedef  char const *  c_cstring;

// Predicate

// char == char Case-Insensitively?
inline
bool
equali_char( char const c, char const d )
{
	return ( to_lower( c ) == to_lower( d ) );
}

// string == string Case-Insensitively?
inline
bool
equali( std::string const & s, std::string const & t )
{
	return ( s.length() == t.length() ? std::equal( s.begin(), s.end(), t.begin(), equali_char ) : false );
}

// string == cstring Case-Insensitively?
inline
bool
equali( std::string const & s, c_cstring const t )
{
	return ( s.length() == std::strlen( t ) ? std::equal( s.begin(), s.end(), t, equali_char ) : false );
}

// cstring == string Case-Insensitively?
inline
bool
equali( c_cstring const s, std::string const & t )
{
	return ( std::strlen( s ) == t.length() ? std::equal( t.begin(), t.end(), s, equali_char ) : false );
}

// cstring == cstring Case-Insensitively?
inline
bool
equali( c_cstring const s, c_cstring const t )
{
	auto const s_len( std::strlen( s ) );
	return ( s_len == std::strlen( t ) ? std::equal( s, s + s_len, t, equali_char ) : false );
}

// string == string Case-Optionally?
inline
bool
equal( std::string const & s, std::string const & t, bool const exact_case = true )
{
	return ( exact_case ? s == t : equali( s, t ) );
}

// string == string Case-Optionally?
inline
bool
equal( std::string const & s, c_cstring const t, bool const exact_case = true )
{
	return ( exact_case ? s == t : equali( s, t ) );
}

// string == string Case-Optionally?
inline
bool
equal( c_cstring const s, std::string const & t, bool const exact_case = true )
{
	return ( std::strlen( s ) == t.length() ? ( exact_case ? std::equal( t.begin(), t.end(), s ) : std::equal( t.begin(), t.end(), s, equali_char ) ) : false );
}

// string == string Case-Optionally?
inline
bool
equal( c_cstring const s, c_cstring const t, bool const exact_case = true )
{
	auto const s_len( std::strlen( s ) );
	return ( s_len == std::strlen( t ) ? ( exact_case ? std::equal( s, s + s_len, t ) : std::equal( s, s + s_len, t, equali_char ) ) : false );
}

// string is Empty?
inline
bool
empty( std::string const & s )
{
	return s.empty();
}

// string is Blank?
inline
bool
is_blank( std::string const & s )
{
	return ( s.empty() ? true : s.find_first_not_of( ' ' ) == std::string::npos );
}

// string is Not Blank?
inline
bool
not_blank( std::string const & s )
{
	return ! is_blank( s );
}

// string is Whitespace?
inline
bool
is_whitespace( std::string const & s )
{
	return ( s.empty() ? true : s.find_last_not_of( " \t\000" ) == std::string::npos );
}

// string is Not Whitespace?
inline
bool
not_whitespace( std::string const & s )
{
	return ! is_whitespace( s );
}

// string is Alphabetic?
inline
bool
is_alpha( std::string const & s )
{
	if ( s.empty() ) {
		return false;
	} else {
		for ( char const c : s ) {
			if ( ! isalpha( c ) ) return false;
		}
		return true;
	}
}

// string is Digits?
inline
bool
is_digit( std::string const & s )
{
	if ( s.empty() ) {
		return false;
	} else {
		for ( char const c : s ) {
			if ( ! isdigit( c ) ) return false;
		}
		return true;
	}
}

// string has a string?
inline
bool
has( std::string const & s, std::string const & t )
{
	return ( s.find( t ) != std::string::npos );
}

// string has a cstring?
inline
bool
has( std::string const & s, c_cstring const t )
{
	return ( s.find( t ) != std::string::npos );
}

// string has a Character?
inline
bool
has( std::string const & s, char const c )
{
	return ( s.find( c ) != std::string::npos );
}

// string has a String/Character Case-Insensitively?
template< typename T >
bool
hasi( std::string const & s, T const & t ); // Implementation below

// string has any Character of a string?
inline
bool
has_any_of( std::string const & s, std::string const & t )
{
	return ( s.find_first_of( t ) != std::string::npos );
}

// string has any Character of a cstring?
inline
bool
has_any_of( std::string const & s, c_cstring const t )
{
	return ( s.find_first_of( t ) != std::string::npos );
}

// string has a Character?
inline
bool
has_any_of( std::string const & s, char const c )
{
	return ( s.find_first_of( c ) != std::string::npos );
}

// string has any Character of a string?
inline
bool
has_any_not_of( std::string const & s, std::string const & t )
{
	return ( s.find_first_not_of( t ) != std::string::npos );
}

// string has any Character of a cstring?
inline
bool
has_any_not_of( std::string const & s, c_cstring const t )
{
	return ( s.find_first_not_of( t ) != std::string::npos );
}

// string has a Character?
inline
bool
has_any_not_of( std::string const & s, char const c )
{
	return ( s.find_first_not_of( c ) != std::string::npos );
}

// Has a Prefix Case-Optionally?
bool
has_prefix( std::string const & s, std::string const & pre, bool const exact_case = true );

// Has a Prefix Case-Optionally?
bool
has_prefix( std::string const & s, c_cstring const pre, bool const exact_case = true );

// Has a Prefix Case-Optionally?
bool
has_prefix( std::string const & s, char const pre, bool const exact_case = true );

// Has a Prefix Case-Insensitively?
template< typename S >
inline
bool
has_prefixi( std::string const & s, S const & pre )
{
	return has_prefix( s, pre, false );
}

// Has a Suffix Case-Optionally?
bool
has_suffix( std::string const & s, std::string const & suf, bool const exact_case = true );

// Has a Suffix Case-Optionally?
bool
has_suffix( std::string const & s, c_cstring const suf, bool const exact_case = true );

// Has a Suffix Case-Optionally?
bool
has_suffix( std::string const & s, char const suf, bool const exact_case = true );

// Has a Suffix Case-Insensitively?
template< typename S >
inline
bool
has_suffixi( std::string const & s, S const & suf )
{
	return has_suffix( s, suf, false );
}

// Inspector

// Length
inline
std::string::size_type
len( std::string const & s )
{
	return s.length();
}

// Length Space-Trimmed
inline
std::string::size_type
len_trim( std::string const & s )
{
	return s.find_last_not_of( ' ' ) + 1; // Works if npos returned: npos + 1 == 0
}

// Length Whitespace-Trimmed
inline
std::string::size_type
len_trim_whitespace( std::string const & s )
{
	return s.find_last_not_of( " \t\000" ) + 1; // Works if npos returned: npos + 1 == 0
}

// Index of a Substring
template< typename T >
inline
std::string::size_type
index( std::string const & s, T const & t, bool const last = false )
{
	return ( last ? s.rfind( t ) : s.find( t ) );
}

// Last Index of a Substring
template< typename T >
inline
std::string::size_type
rindex( std::string const & s, T const & t )
{
	return index( s, t, true );
}

// Index of a Substring Case-Insensitively
inline
std::string::size_type
indexi( std::string const & s, std::string const & t, bool const last = false )
{
	if ( last ) {
		auto const i( std::find_end( s.begin(), s.end(), t.begin(), t.end(), equali_char ) );
		return ( i == s.end() ? std::string::npos : static_cast< std::string::size_type >( i - s.begin() ) );
	} else {
		auto const i( std::search( s.begin(), s.end(), t.begin(), t.end(), equali_char ) );
		return ( i == s.end() ? std::string::npos : static_cast< std::string::size_type >( i - s.begin() ) );
	}
}

// Index of a Substring Case-Insensitively
inline
std::string::size_type
indexi( std::string const & s, c_cstring const t, bool const last = false )
{
	if ( last ) {
		auto const i( std::find_end( s.begin(), s.end(), t, t + std::strlen( t ), equali_char ) );
		return ( i == s.end() ? std::string::npos : static_cast< std::string::size_type >( i - s.begin() ) );
	} else {
		auto const i( std::search( s.begin(), s.end(), t, t + std::strlen( t ), equali_char ) );
		return ( i == s.end() ? std::string::npos : static_cast< std::string::size_type >( i - s.begin() ) );
	}
}

// Index of a Character Case-Insensitively
inline
std::string::size_type
indexi( std::string const & s, char const c, bool const last = false )
{
	if ( last ) {
		for ( std::string::size_type i = s.length() - 1, e = 0; i >= e; --i ) {
			if ( equali_char( s[ i ], c ) ) return i;
		}
	} else {
		for ( std::string::size_type i = 0, e = s.length(); i < e; ++i ) {
			if ( equali_char( s[ i ], c ) ) return i;
		}
	}
	return std::string::npos;
}

// Last Index of a Substring Case-Insensitively
template< typename T >
inline
std::string::size_type
rindexi( std::string const & s, T const & t )
{
	return indexi( s, t, true );
}

// string has a String/Character Case-Insensitively?
template< typename T >
inline
bool
hasi( std::string const & s, T const & t )
{
	return ( indexi( s, t ) != std::string::npos );
}

// Find any Characters of Another String
inline
std::string::size_type
scan( std::string const & s, std::string const & t, bool const last = false )
{
	return ( last ? s.find_last_of( t ) : s.find_first_of( t ) );
}

// Find any Characters of Another String
inline
std::string::size_type
scan( std::string const & s, c_cstring const t, bool const last = false )
{
	return ( last ? s.find_last_of( t ) : s.find_first_of( t ) );
}

// Find a Character
inline
std::string::size_type
scan( std::string const & s, char const c, bool const last = false )
{
	return ( last ? s.find_last_of( c ) : s.find_first_of( c ) );
}

// Find any Characters not of Another String
inline
std::string::size_type
verify( std::string const & s, std::string const & t, bool const last = false )
{
	return ( last ? s.find_last_not_of( t ) : s.find_first_not_of( t ) );
}

// Find any Characters not of Another String
inline
std::string::size_type
verify( std::string const & s, c_cstring const t, bool const last = false )
{
	return ( last ? s.find_last_not_of( t ) : s.find_first_not_of( t ) );
}

// Find Character not a Character
inline
std::string::size_type
verify( std::string const & s, char const c, bool const last = false )
{
	return ( last ? s.find_last_not_of( c ) : s.find_first_not_of( c ) );
}

// Modifier

// Lowercase a string
std::string &
lowercase( std::string & s );

// Uppercase a string
std::string &
uppercase( std::string & s );

// Left Justify a string
std::string &
left_justify( std::string & s );

// Left Justify a string
inline
std::string &
ljustify( std::string & s )
{
	return left_justify( s );
}

// Right Justify a string
std::string &
right_justify( std::string & s );

// Right Justify a string
inline
std::string &
rjustify( std::string & s )
{
	return right_justify( s );
}

// Trim Trailing Space from a string
std::string &
trim( std::string & s );

// Trim Trailing Whitespace from a string
std::string &
trim_whitespace( std::string & s );

// Strip Specified Characters from a string's Tails
std::string &
strip( std::string & s, std::string const & chars );

// Strip Specified Characters from a string's Left Tail
std::string &
lstrip( std::string & s, std::string const & chars );

// Strip Specified Characters from a string's Right Tail
std::string &
rstrip( std::string & s, std::string const & chars );

// Strip Space from a string's Tails
std::string &
strip( std::string & s );

// Strip Space from a string's Left Tail
std::string &
lstrip( std::string & s );

// Strip Space from a string's Right Tail
std::string &
rstrip( std::string & s );

// Strip Whitespace from a string's Tails
std::string &
strip_whitespace( std::string & s );

// Strip Whitespace from a string's Left Tail
std::string &
lstrip_whitespace( std::string & s );

// Strip Whitespace from a string's Right Tail
std::string &
rstrip_whitespace( std::string & s );

// Pad a string to a Specified Length
inline
std::string &
pad( std::string & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	if ( s_len < len ) s.append( len - s_len, ' ' ); // Pad
	return s;
}

// Left-Pad a string to a Specified Length
inline
std::string &
lpad( std::string & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	if ( s_len < len ) s.insert( static_cast< std::string::size_type >( 0 ), len - s_len, ' ' ); // Left-pad
	return s;
}

// Right-Pad a string to a Specified Length
inline
std::string &
rpad( std::string & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	if ( s_len < len ) s.append( len - s_len, ' ' ); // Pad
	return s;
}

// Pare a string to a Specified Length
inline
std::string &
pare( std::string & s, std::string::size_type const len )
{
	if ( s.length() > len ) s.erase( len ); // Pare
	return s;
}

// Left-Pare a string to a Specified Length
inline
std::string &
lpare( std::string & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	if ( s_len > len ) s.erase( 0, s_len - len ); // Pare
	return s;
}

// Right-Pare a string to a Specified Length
inline
std::string &
rpare( std::string & s, std::string::size_type const len )
{
	if ( s.length() > len ) s.erase( len ); // Pare
	return s;
}

// Size a string to a Specified Length
std::string &
size( std::string & s, std::string::size_type const len );

// Center a string wrt its Whitespace
std::string &
center( std::string & s );

// Center a string with a Specified Length
std::string &
center( std::string & s, std::string::size_type const len );

// Remove Repeat Characters from a Possibly Unsorted string Preserving Order
std::string &
unique( std::string & s );

// Substring Replaced in a string
std::string &
replace( std::string & s, std::string const & a, std::string const & b );

// Wrap in Double Quotes
inline
std::string &
quote( std::string & s )
{
	s = '"' + s + '"';
	return s;
}

// Overlay a string with Another string, Expanding Size as Needed
std::string &
overlay( std::string & s, std::string const & t, std::string::size_type const pos = 0 );

// Generator

// Blank string of Specified Length
inline
std::string
blank( std::string::size_type const len )
{
	return std::string( len, ' ' );
}

// Lowercased Copy of a string
std::string
lowercased( std::string const & s );

// Uppercased Copy of a string
std::string
uppercased( std::string const & s );

// Left-Justified Copy of a string
std::string
left_justified( std::string const & s );

// Left-Justified Copy of a string
inline
std::string
ljustified( std::string const & s )
{
	return left_justified( s );
}

// Right-Justified Copy of a string
std::string
right_justified( std::string const & s );

// Right-Justified Copy of a string
inline
std::string
rjustified( std::string const & s )
{
	return right_justified( s );
}

// Trailing Space Trimmed Copy of a string
std::string
trimmed( std::string const & s );

// Trailing Whitespace Trimmed Copy of a string
std::string
trimmed_whitespace( std::string const & s );

// Specified Characters Stripped from a string's Tails Copy of a string
std::string
stripped( std::string const & s, std::string const & chars );

// Specified Characters Stripped from a string's Left Tail Copy of a string
std::string
lstripped( std::string const & s, std::string const & chars );

// Specified Characters Stripped from a string's Right Tail Copy of a string
std::string
rstripped( std::string const & s, std::string const & chars );

// Space Stripped from a string's Tails Copy of a string
std::string
stripped( std::string const & s );

// Space Stripped from a string's Left Tail Copy of a string
std::string
lstripped( std::string const & s );

// Space Stripped from a string's Right Tail Copy of a string
std::string
rstripped( std::string const & s );

// Whitespace Stripped from a string's Tails Copy of a string
std::string
stripped_whitespace( std::string const & s );

// Whitespace Stripped from a string's Left Tail Copy of a string
std::string
lstripped_whitespace( std::string const & s );

// Whitespace Stripped from a string's Right Tail Copy of a string
std::string
rstripped_whitespace( std::string const & s );

// Padded to a Specified Length Copy of a string
inline
std::string
padded( std::string const & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	return ( s_len < len ? s + std::string( len - s_len, ' ' ) : s );
}

// Left-Padded to a Specified Length Copy of a string
inline
std::string
lpadded( std::string const & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	return ( s_len < len ? std::string( len - s_len, ' ' ).append( s ) : s );
}

// Right-Padded to a Specified Length Copy of a string
inline
std::string
rpadded( std::string const & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	return ( s_len < len ? s + std::string( len - s_len, ' ' ) : s );
}

// Pared to a Specified Length Copy of a string
inline
std::string
pared( std::string const & s, std::string::size_type const len )
{
	return ( s.length() > len ? std::string( s, 0, len ) : s );
}

// Left-Pared to a Specified Length Copy of a string
inline
std::string
lpared( std::string const & s, std::string::size_type const len )
{
	std::string::size_type const s_len( s.length() );
	return ( s_len > len ? std::string( s, s_len - len ) : s );
}

// Right-Pared to a Specified Length Copy of a string
inline
std::string
rpared( std::string const & s, std::string::size_type const len )
{
	return ( s.length() > len ? std::string( s, 0, len ) : s );
}

// Sized to a Specified Length Copy of a string
std::string
sized( std::string const & s, std::string::size_type const len );

// Left-Sized to a Specified Length Copy of a string
std::string
lsized( std::string const & s, std::string::size_type const len );

// Right-Sized to a Specified Length Copy of a string
inline
std::string
rsized( std::string const & s, std::string::size_type const len )
{
	return sized( s, len );
}

// Centered in a string of Specified Length Copy of a string
std::string
centered( std::string const & s, std::string::size_type const len );

// Centered wrt Whitespace Copy of a string
inline
std::string
centered( std::string const & s )
{
	return centered( stripped_whitespace( s ), s.length() );
}

// Removed Repeat Characters from a Possibly Unsorted string Preserving Order Copy of a string
std::string
uniqued( std::string const & s );

// Substring Replaced Copy of a string
inline
std::string
replaced( std::string const & s, std::string const & a, std::string const & b )
{
	std::string r( s );
	replace( r, a, b );
	return r;
}

// Wrapped in Double Quotes Copy of a String
inline
std::string
quoted( std::string & s )
{
	return std::string( '"' + s + '"' );
}

// Space-Free Head Copy of a string
std::string
head( std::string const & s );

// Conversion To std::string

// string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
string_of( T const & t )
{
	std::ostringstream t_stream;
	t_stream << std::uppercase << std::setprecision( TypeTraits< T >::precision() ) << t;
	return t_stream.str();
}

// string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
string_of(
	T const & t,
	int const p // Precision
)
{
	std::ostringstream t_stream;
	t_stream << std::uppercase << std::setprecision( p ) << t;
	return t_stream.str();
}

// Left-Justified string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
left_string_of(
	T const & t,
	int const w, // Minimum width
	char const f = ' ' // Fill character
)
{
	std::ostringstream t_stream;
	t_stream << std::left << std::uppercase
	 << std::setw( w ) << std::setfill( f ) << std::setprecision( TypeTraits< T >::precision() ) << t;
	return t_stream.str();
}

// Right-Justified string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
right_string_of(
	T const & t,
	int const w, // Minimum width
	char const f = ' ' // Fill character
)
{
	std::ostringstream t_stream;
	t_stream << std::right << std::uppercase
	 << std::setw( w ) << std::setfill( f ) << std::setprecision( TypeTraits< T >::precision() ) << t;
	return t_stream.str();
}

// Leading-Zero Right-Justified string of a Template Argument Type Supporting Stream Output
// Negative numbers appear with the minus sign on the left of the filled zeros
template< typename T >
inline
std::string
lead_zero_string_of(
	T const & t,
	int const w // Minimum width
)
{
	std::ostringstream t_stream;
	t_stream << std::internal << std::uppercase
	 << std::setw( w ) << std::setfill( '0' ) << std::setprecision( TypeTraits< T >::precision() ) << t;
	return t_stream.str();
}

// Right-Justified General Format string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
general_string_of(
	T const & t,
	int const w = TypeTraits< T >::width(), // Minimum width
	int const p = TypeTraits< T >::precision() // Precision
)
{
	std::ostringstream t_stream;
	t_stream << std::right << std::uppercase << std::showpoint
	 << std::setw( w ) << std::setprecision( p ) << t;
	return t_stream.str();
}

// Right-Justified Fixed Format string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
fixed_string_of(
	T const & t,
	int const w = TypeTraits< T >::width(), // Minimum width
	int const p = TypeTraits< T >::precision() // Precision
)
{
	std::ostringstream t_stream;
	t_stream << std::right << std::uppercase << std::fixed << std::showpoint
	 << std::setw( w ) << std::setprecision( p ) << t;
	return t_stream.str();
}

// Right-Justified Scientific Format string of a Template Argument Type Supporting Stream Output
template< typename T >
inline
std::string
scientific_string_of(
	T const & t,
	int const w = TypeTraits< T >::width(), // Minimum width
	int const p = TypeTraits< T >::precision() // Precision
)
{
	std::ostringstream t_stream;
	t_stream << std::right << std::uppercase << std::scientific << std::showpoint
	 << std::setw( w ) << std::setprecision( p ) << t;
	return t_stream.str();
}

// Conversion From std::string

// string is Readable as a Type Supporting Stream Input?
template< typename T >
inline
bool
is_type( std::string const & s )
{
	if ( is_whitespace( s ) ) { // Don't accept empty or whitespace string
		return false;
	} else { // Try to read the string as a T
		std::istringstream t_stream( trimmed_whitespace( s ) );
		T t;
		t_stream >> t;
		return ( ( t_stream ) && ( t_stream.eof() ) );
	}
}

// string is Readable as a char Supporting Stream Input?
template<>
inline
bool
is_type< char >( std::string const & s )
{
	return ( s.length() == 1 );
}

// string is Readable as a bool?
inline
bool
is_bool( std::string const & s )
{
	return is_type< bool >( s );
}

// string is Readable as a short int?
inline
bool
is_short( std::string const & s )
{
	return is_type< short int >( s );
}

// string is Readable as an int?
inline
bool
is_int( std::string const & s )
{
	return is_type< int >( s );
}

// string is Readable as a long int?
inline
bool
is_long( std::string const & s )
{
	return is_type< long int >( s );
}

// string is Readable as an unsigned short int?
inline
bool
is_ushort( std::string const & s )
{
	return is_type< unsigned short int >( s );
}

// string is Readable as an unsigned int?
inline
bool
is_uint( std::string const & s )
{
	return is_type< unsigned int >( s );
}

// string is Readable as an unsigned long int?
inline
bool
is_ulong( std::string const & s )
{
	return is_type< unsigned long int >( s );
}

// string is Readable as a float?
inline
bool
is_float( std::string const & s )
{
	return is_type< float >( s );
}

// string is Readable as a double?
inline
bool
is_double( std::string const & s )
{
	return is_type< double >( s );
}

// string is Readable as a long double?
inline
bool
is_longdouble( std::string const & s )
{
	return is_type< long double >( s );
}

// string is Readable as a char?
inline
bool
is_char( std::string const & s )
{
	return is_type< char >( s );
}

// string is Readable as a Decimal Integer?
bool
is_decimal( std::string const & s, bool const allow_sign = true );

// string is Readable as a Binary Integer?
bool
is_binary( std::string const & s, bool const allow_sign = true );

// string is Readable as an Octal Integer?
bool
is_octal( std::string const & s, bool const allow_sign = true );

// string is Readable as a Hexidecimal Integer?
bool
is_hexidecimal( std::string const & s, bool const allow_sign = true );

// Type of a string for Type Supporting Stream Input
template< typename T >
inline
T
type_of( std::string const & s )
{
	std::istringstream t_stream( trimmed_whitespace( s ) );
	T t;
	t_stream >> t;
	return ( t_stream && t_stream.eof() ? t : T() ); // Check is_type first
}

// char of a string
template<>
inline
char
type_of< char >( std::string const & s )
{
	return ( s.length() == 1 ? s[ 0 ] : char() ); // Check is_type first
}

// short int of a string
inline
short int
short_of( std::string const & s )
{
	return type_of< short int >( s );
}

// int of a string
inline
int
int_of( std::string const & s )
{
	return type_of< int >( s );
}

// long int of a string
inline
long int
long_of( std::string const & s )
{
	return type_of< long int >( s );
}

// unsigned short int of a string
inline
unsigned short int
ushort_of( std::string const & s )
{
	return type_of< unsigned short int >( s );
}

// unsigned int of a string
inline
unsigned int
uint_of( std::string const & s )
{
	return type_of< unsigned int >( s );
}

// unsigned long int of a string
inline
unsigned long int
ulong_of( std::string const & s )
{
	return type_of< unsigned long int >( s );
}

// float of a string
inline
float
float_of( std::string const & s )
{
	return type_of< float >( s );
}

// double of a string
inline
double
double_of( std::string const & s )
{
	return type_of< double >( s );
}

// long double of a string
inline
long double
longdouble_of( std::string const & s )
{
	return type_of< long double >( s );
}

// long double of a string
inline
long double
long_double_of( std::string const & s )
{
	return type_of< long double >( s );
}

// char of a string
inline
char
char_of( std::string const & s )
{
	return type_of< char >( s );
}

// long int of a Decimal string
inline
long int
decimal_of( std::string const & s )
{
	return strtol( s.c_str(), nullptr, 10 );
}

// long int of a Binary string
inline
long int
binary_of( std::string const & s )
{
	return strtol( s.c_str(), nullptr, 2 );
}

// long int of an Octal string
inline
long int
octal_of( std::string const & s )
{
	return strtol( s.c_str(), nullptr, 8 );
}

// long int of a Hexidecimal string
inline
long int
hexidecimal_of( std::string const & s )
{
	return strtol( s.c_str(), nullptr, 16 );
}

} // ObjexxFCL

#endif // ObjexxFCL_string_functions_hh_INCLUDED
