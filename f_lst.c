#include "philosopher.h"


t_arg_t	*ft_lstnew(void *content)
{
	t_arg_t	*_str;

	_str = malloc(sizeof(t_arg_t));
	if (!_str)
		return (0);
	if (_str)
	{
		_str->content ;
		_str->next = NULL;
	}
	return (_str);
}
