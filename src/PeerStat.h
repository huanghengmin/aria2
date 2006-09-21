/* <!-- copyright */
/*
 * aria2 - a simple utility for downloading files faster
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/* copyright --> */
#ifndef _D_PEER_STAT_H_
#define _D_PEER_STAT_H_

#include "common.h"
#include "SpeedCalc.h"
#include "SharedHandle.h"

class PeerStat {
public:
  enum STATUS {
    IDLE,
    ACTIVE,
    REQUEST_IDLE,
  };
private:
  int cuid;
  SpeedCalc downloadSpeed;
  SpeedCalc uploadSpeed;
  Time downloadStartTime;
  STATUS status;
public:

  PeerStat(int cuid = 0):cuid(cuid), status(IDLE) {}

  ~PeerStat() {}

  /**
   * Returns current download speed in byte per sec.
   */
  int calculateDownloadSpeed() {
    return downloadSpeed.calculateSpeed();
  }

  int calculateUploadSpeed() {
    return uploadSpeed.calculateSpeed();
  }

  void updateDownloadLength(int bytes) {
    downloadSpeed.update(bytes);
  }

  void updateUploadLength(int bytes) {
    uploadSpeed.update(bytes);
  }

  int getMaxDownloadSpeed() const {
    return downloadSpeed.getMaxSpeed();
  }

  int getMaxUploadSpeed() const {
    return uploadSpeed.getMaxSpeed();
  }

  int getAvgDownloadSpeed() const {
    return downloadSpeed.getAvgSpeed();
  }

  int getAvgUploadSpeed() const {
    return uploadSpeed.getAvgSpeed();
  }

  void reset() {
    downloadSpeed.reset();
    uploadSpeed.reset();
    downloadStartTime.reset();
    status = IDLE;
  }

  void downloadStart() {
    reset();
    status = ACTIVE;
  }

  void downloadStop() {
    status = IDLE;
  }

  void requestIdle() {
    status = REQUEST_IDLE;
  }

  const Time& getDownloadStartTime() const {
    return downloadStartTime;
  }

  STATUS getStatus() const {
    return status;
  }

  int getCuid() const {
    return cuid;
  }
};

typedef SharedHandle<PeerStat> PeerStatHandle;

#endif // _D_PEER_STAT_H_
