/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <QWaitCondition>
#include <QMutex>
#include <QDebug>

#include "acquisitionthread.h"

namespace {

QWaitCondition cond_acquire;
QMutex* mutex = new QMutex;

//std::ofstream ff("output.txt");

} // namespace

AcquireThread::AcquireThread(QObject* parent)
  :
  QThread(parent),
  stopped(false)
{
}

AcquireThread::~AcquireThread()
{
}

void
AcquireThread::stop()
{
  QMutexLocker locker(mutex);
  stopped = true;
}

void
AcquireThread::run()
{
  while (true)
  {
    {
      QMutexLocker locker(mutex);
        if (stopped)
        {
          break;
        }
      }
  }
  stopped = false;
}
