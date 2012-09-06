/* 
 * Registry file
 *
 * Copyright (c) 2011-2012, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "evttools_libcerror.h"
#include "evttools_libcstring.h"
#include "evttools_libregf.h"
#include "registry_file.h"

/* Initializes the registry file
 * Returns 1 if successful or -1 on error
 */
int registry_file_initialize(
     registry_file_t **registry_file,
     libcerror_error_t **error )
{
	static char *function = "registry_file_initialize";

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( *registry_file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid registry file value already set.",
		 function );

		return( -1 );
	}
	*registry_file = memory_allocate_structure(
	                  registry_file_t );

	if( *registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create registry file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *registry_file,
	     0,
	     sizeof( registry_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear registry file.",
		 function );

		memory_free(
		 *registry_file );

		*registry_file = NULL;

		return( -1 );
	}
	if( libregf_file_initialize(
	     &( ( *registry_file )->regf_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize REGF file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *registry_file != NULL )
	{
		memory_free(
		 *registry_file );

		*registry_file = NULL;
	}
	return( -1 );
}

/* Frees the registry file and its elements
 * Returns 1 if successful or -1 on error
 */
int registry_file_free(
     registry_file_t **registry_file,
     libcerror_error_t **error )
{
	static char *function = "registry_file_free";
	int result            = 1;

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( *registry_file != NULL )
	{
		if( ( *registry_file )->is_open != 0 )
		{
			if( registry_file_close(
			     *registry_file,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close registry file.",
				 function );

				result = -1;
			}
		}
		if( libregf_file_free(
		     &( ( *registry_file )->regf_file ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free REGF file.",
			 function );

			result = -1;
		}
		memory_free(
		 *registry_file );

		*registry_file = NULL;
	}
	return( result );
}

/* Signals the registry file to abort
 * Returns 1 if successful or -1 on error
 */
int registry_file_signal_abort(
     registry_file_t *registry_file,
     libcerror_error_t **error )
{
	static char *function = "registry_file_signal_abort";

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( registry_file->regf_file != NULL )
	{
		if( libregf_file_signal_abort(
		     registry_file->regf_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal REGF file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int registry_file_set_ascii_codepage(
     registry_file_t *registry_file,
     int ascii_codepage,
     libcerror_error_t **error )
{
	static char *function  = "registry_file_set_ascii_codepage";

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( libregf_file_set_ascii_codepage(
	     registry_file->regf_file,
	     ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set ASCII codepage in REGF file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Opens the registry file
 * Returns 1 if successful or -1 on error
 */
int registry_file_open(
     registry_file_t *registry_file,
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	libregf_key_t *sub_key     = NULL;
	libregf_value_t *value     = NULL;
	static char *function      = "registry_file_open";
	const char *sub_key_path   = NULL;
	const char *value_name     = NULL;
	size_t sub_key_path_length = 0;
	size_t value_name_length   = 0;
	int number_of_sub_keys     = 0;
	int result                 = 0;

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( registry_file->is_open != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid registry file already open.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libregf_file_open_wide(
	     registry_file->regf_file,
	     filename,
	     LIBREGF_OPEN_READ,
	     error ) != 1 )
#else
	if( libregf_file_open(
	     registry_file->regf_file,
	     filename,
	     LIBREGF_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open REGF file.",
		 function );

		goto on_error;
	}
	if( libregf_file_get_root_key(
	     registry_file->regf_file,
	     &( registry_file->root_key ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve root key.",
		 function );

		goto on_error;
	}
	if( libregf_key_get_number_of_sub_keys(
	     registry_file->root_key,
	     &number_of_sub_keys,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub keys.",
		 function );

		goto on_error;
	}
	if( number_of_sub_keys == 1 )
	{
/* TODO make sure to check key name */
		if( libregf_key_get_sub_key(
		     registry_file->root_key,
		     0,
		     &( registry_file->base_key ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve base key.",
			 function );

			goto on_error;
		}
	}
	else if( number_of_sub_keys > 1 )
	{
		registry_file->base_key = registry_file->root_key;
	}
	if( libregf_key_get_number_of_sub_keys(
	     registry_file->base_key,
	     &number_of_sub_keys,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub keys.",
		 function );

		goto on_error;
	}
/* TODO - or look for specific keys that are useful to have in the first place ? */
#ifdef TODO
	int sub_key_index          = 0;

	/* Determine which registry file type this is based on
	 * the sub keys of the base key
	 */
	for( sub_key_index = 0;
	     sub_key_index < number_of_sub_keys;
	     sub_key_index++ )
	{
	}
#endif
	/* Get the current control set from:
	 * SYSTEM\Select\Current
	 */
	sub_key_path = "Select";

	sub_key_path_length = libcstring_narrow_string_length(
	                       sub_key_path );

	result = libregf_key_get_sub_key_by_utf8_path(
		  registry_file->base_key,
		  (uint8_t *) sub_key_path,
		  sub_key_path_length,
		  &sub_key,
		  error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub key: %s.",
		 function,
		 sub_key_path );

		goto on_error;
	}
	else if( result != 0 )
	{
		value_name = "Current";

		value_name_length = libcstring_narrow_string_length(
		                     value_name );

		result = libregf_key_get_value_by_utf8_name(
			  sub_key,
			  (uint8_t *) value_name,
			  value_name_length,
			  &value,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value: %s.",
			 function,
			 value_name );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( libregf_value_get_value_32bit(
			     value,
			     &( registry_file->current_control_set ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 32-bit value: %s.",
				 function,
				 value_name );

				goto on_error;
			}
			if( libregf_value_free(
			     &value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free value.",
				 function );

				goto on_error;
			}
		}
	}
	if( libregf_key_free(
	     &sub_key,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free sub key.",
		 function );

		goto on_error;
	}
	/* Retrieve the control set 1 key: SYSTEM\ControlSet001
	 */
	sub_key_path = "ControlSet001";

	sub_key_path_length = libcstring_narrow_string_length(
	                       sub_key_path );

	result = libregf_key_get_sub_key_by_utf8_path(
		  registry_file->base_key,
		  (uint8_t *) sub_key_path,
		  sub_key_path_length,
		  &( registry_file->control_set1_key ),
		  error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub key: %s.",
		 function,
		 sub_key_path );

		goto on_error;
	}
	/* Retrieve the control set 2 key: SYSTEM\ControlSet002
	 */
	sub_key_path = "ControlSet002";

	sub_key_path_length = libcstring_narrow_string_length(
	                       sub_key_path );

	result = libregf_key_get_sub_key_by_utf8_path(
		  registry_file->base_key,
		  (uint8_t *) sub_key_path,
		  sub_key_path_length,
		  &( registry_file->control_set2_key ),
		  error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub key: %s.",
		 function,
		 sub_key_path );

		goto on_error;
	}
	if( ( registry_file->current_control_set != 0 )
	 || ( registry_file->control_set1_key != NULL )
	 || ( registry_file->control_set2_key != NULL ) )
	{
		if( ( registry_file->current_control_set != 1 )
		 && ( registry_file->current_control_set != 2 ) )
		{
/* TODO print debug notification */
			registry_file->current_control_set = 1;
		}
		if( ( registry_file->current_control_set == 1 )
		 && ( registry_file->control_set1_key != NULL ) )
		{
			registry_file->current_control_set_key = registry_file->control_set1_key;
		}
		else if( ( registry_file->current_control_set == 2 )
		      && ( registry_file->control_set2_key != NULL ) )
		{
			registry_file->current_control_set_key = registry_file->control_set2_key;
		}
	}
	registry_file->is_open = 1;

	return( 1 );

on_error:
	if( value != NULL )
	{
		libregf_value_free(
		 &value,
		 NULL );
	}
	if( sub_key != NULL )
	{
		libregf_key_free(
		 &sub_key,
		 NULL );
	}
	if( registry_file->control_set2_key != NULL )
	{
		libregf_key_free(
		 &( registry_file->control_set2_key ),
		 NULL );
	}
	if( registry_file->control_set1_key != NULL )
	{
		libregf_key_free(
		 &( registry_file->control_set1_key ),
		 NULL );
	}
	if( ( registry_file->base_key != NULL )
	 && ( registry_file->base_key != registry_file->root_key ) )
	{
		libregf_key_free(
		 &( registry_file->base_key ),
		 NULL );
	}
	if( registry_file->root_key != NULL )
	{
		libregf_key_free(
		 &( registry_file->root_key ),
		 NULL );
	}
	libregf_file_close(
	 registry_file->regf_file,
	 NULL );

	return( -1 );
}

/* Closes the registry file
 * Returns the 0 if succesful or -1 on error
 */
int registry_file_close(
     registry_file_t *registry_file,
     libcerror_error_t **error )
{
	static char *function = "registry_file_close";
	int result            = 0;

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
	if( registry_file->is_open != 0 )
	{
		if( registry_file->control_set2_key != NULL )
		{
			if( libregf_key_free(
			     &( registry_file->control_set2_key ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free control set 2 key.",
				 function );

				result = -1;
			}
		}
		if( registry_file->control_set1_key != NULL )
		{
			if( libregf_key_free(
			     &( registry_file->control_set1_key ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free control set 1 key.",
				 function );

				result = -1;
			}
		}
		if( ( registry_file->base_key != NULL )
		 && ( registry_file->base_key != registry_file->root_key ) )
		{
			if( libregf_key_free(
			     &( registry_file->base_key ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free base key.",
				 function );

				result = -1;
			}
		}
		if( registry_file->root_key != NULL )
		{
			if( libregf_key_free(
			     &( registry_file->root_key ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free root key.",
				 function );

				result = -1;
			}
		}
		if( libregf_file_close(
		     registry_file->regf_file,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close REGF file.",
			 function );

			result = -1;
		}
		registry_file->is_open = 0;
	}
	return( result );
}

/* Retrieves the key specified by the path
 * Returns 1 if successful or -1 on error
 */
int registry_file_get_key_by_path(
     registry_file_t *registry_file,
     const libcstring_system_character_t *key_path,
     size_t key_path_length,
     libregf_key_t **key,
     libcerror_error_t **error )
{
	static char *function = "registry_file_get_key_by_path";
	int result            = 0;

	if( registry_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid registry file.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libregf_key_get_sub_key_by_utf16_path(
	          registry_file->base_key,
	          (uint16_t *) key_path,
	          key_path_length,
	          key,
	          error );
#else
	result = libregf_key_get_sub_key_by_utf8_path(
	          registry_file->base_key,
	          (uint8_t *) key_path,
	          key_path_length,
	          key,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve key by path: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 key_path );

		return( -1 );
	}
	return( result );
}
