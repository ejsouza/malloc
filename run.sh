# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esouza <esouza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 10:08:34 by esouza            #+#    #+#              #
#    Updated: 2020/03/09 10:08:42 by esouza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh
export DYLD_LIBRARY_PATH="/Users/esouza/42/malloc/"
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
