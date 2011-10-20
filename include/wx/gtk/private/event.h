///////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/private/event.h
// Purpose:     Helper functions for working with GDK and wx events
// Author:      Vaclav Slavik
// Created:     2011-10-14
// RCS-ID:      $Id$
// Copyright:   (c) 2011 Vaclav Slavik
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _GTK_PRIVATE_EVENT_H_
#define _GTK_PRIVATE_EVENT_H_

namespace wxGTKImpl
{

// init wxMouseEvent with the info from GdkEventXXX struct
template<typename T> void InitMouseEvent(wxWindowGTK *win,
                                         wxMouseEvent& event,
                                         T *gdk_event)
{
    event.m_shiftDown = (gdk_event->state & GDK_SHIFT_MASK) != 0;
    event.m_controlDown = (gdk_event->state & GDK_CONTROL_MASK) != 0;
    event.m_altDown = (gdk_event->state & GDK_MOD1_MASK) != 0;
    event.m_metaDown = (gdk_event->state & GDK_META_MASK) != 0;
    event.m_leftDown = (gdk_event->state & GDK_BUTTON1_MASK) != 0;
    event.m_middleDown = (gdk_event->state & GDK_BUTTON2_MASK) != 0;
    event.m_rightDown = (gdk_event->state & GDK_BUTTON3_MASK) != 0;

    // In gdk/win32 VK_XBUTTON1 is translated to GDK_BUTTON4_MASK
    // and VK_XBUTTON2 to GDK_BUTTON5_MASK. In x11/gdk buttons 4/5
    // are wheel rotation and buttons 8/9 don't change the state.
    event.m_aux1Down = (gdk_event->state & GDK_BUTTON4_MASK) != 0;
    event.m_aux2Down = (gdk_event->state & GDK_BUTTON5_MASK) != 0;

    wxPoint pt = win->GetClientAreaOrigin();
    event.m_x = (wxCoord)gdk_event->x - pt.x;
    event.m_y = (wxCoord)gdk_event->y - pt.y;

    if ((win->m_wxwindow) && (win->GetLayoutDirection() == wxLayout_RightToLeft))
    {
        // origin in the upper right corner
        GtkAllocation a;
        gtk_widget_get_allocation(win->m_wxwindow, &a);
        int window_width = a.width;
        event.m_x = window_width - event.m_x;
    }

    event.SetEventObject( win );
    event.SetId( win->GetId() );
    event.SetTimestamp( gdk_event->time );
}

} // namespace wxGTKImpl

#endif // _GTK_PRIVATE_EVENT_H_
