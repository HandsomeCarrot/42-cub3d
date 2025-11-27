/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:37:11 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/19 10:37:55 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
#define KEYS_H

#ifdef __linux__
    #include <X11/keysym.h>
    #include <X11/X.h>
#elif defined(__APPLE__)
    // Event codes
    #define KeyPress        2
    #define KeyRelease      3
    #define DestroyNotify   17
    
    // Masks (unused on macOS but needed for compatibility)
    #define KeyPressMask    0
    #define KeyReleaseMask  0
    #define NoEventMask     0
    
    // Keycodes
    #define XK_Escape       53
    #define XK_W            13
    #define XK_w            13
    #define XK_A            0
    #define XK_a            0
    #define XK_S            1
    #define XK_s            1
    #define XK_D            2
    #define XK_d            2
    #define XK_Left         123
    #define XK_Right        124
    #define XK_Down         125
    #define XK_Up           126
    #define XK_Shift_L      257
    #define XK_Shift_R      258
#endif

#endif // KEYS_H

