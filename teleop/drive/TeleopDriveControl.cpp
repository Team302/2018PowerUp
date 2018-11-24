/*
 * TeleopDriveControl.cpp
 */

#include <iostream>
#include <interfaces/IDrive.h>

#include <teleop/drive/ArcadeDrive.h>
#include <teleop/drive/TankDrive.h>
#include <teleop/drive/TeleopDrive.h>
#include <teleop/drive/TeleopDriveControl.h>
#include <teleop/controllers/TeleopControl.h>

TeleopDriveControl::TeleopDriveControl() : m_loopCount( 0 ),
                                           m_currentDriveMode( 2 ),
                                           m_driveModes( )
{
    m_driveModes[0] = new ArcadeDrive();
    m_driveModes[1] = new TankDrive();
    m_driveModes[2] = new TeleopDrive();
}

TeleopDriveControl::~TeleopDriveControl()
{
    for ( int inx=0; inx<3; ++inx )
    {
        delete m_driveModes[inx];
    }
}

void TeleopDriveControl::Drive()
{
    m_loopCount++;
    if ( TeleopControl::GetInstance()->IsButtonPressed( TeleopControl::SWITCH_DRIVE_MODE ) && m_loopCount > 50 )
    {
        m_currentDriveMode++;
        if ( m_currentDriveMode > 2)
        {
            m_currentDriveMode = 0;
        }
        m_loopCount = 0;
        printf( "==>> Drive Mode %s \n", m_driveModes[ m_currentDriveMode ]->GetIdentifier() );
    }

    if ( m_driveModes[ m_currentDriveMode ] != nullptr )
    {
//        printf( "==>> Drive Mode %s \n", m_driveModes[ m_currentDriveMode ]->GetIdentifier() );
        m_driveModes[ m_currentDriveMode ]->Drive();
    }
    else
    {
        printf( "==>> no current drive mode \n" );
    }
}

const char* TeleopDriveControl::GetIdentifier() const
{
    const char* mode = nullptr;
    if ( m_driveModes[ m_currentDriveMode ] != nullptr )
    {
        mode = m_driveModes[ m_currentDriveMode ]->GetIdentifier();
    }
    else
    {
        mode = "no current drive mode";
    }
    return mode;
}

