/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#pragma once

#include <deque>
#include <boost/optional.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <Swiften/Network/HostAddressPort.h>
#include <Swiften/Network/PlatformNATTraversalRequest.h>

namespace Swift {

class EventLoop;
class PlatformNATTraversalGetPublicIPRequest;
class PlatformNATTraversalForwardPortRequest;
class PlatformNATTraversalRemovePortForwardingRequest;

class PlatformNATTraversalWorker {
private:
	enum BackendType {
		NotYetDecided,
		UPnP,
		NATPMP,
		None,
	};

public:
	PlatformNATTraversalWorker(EventLoop* eventLoop);
	~PlatformNATTraversalWorker();

	boost::shared_ptr<PlatformNATTraversalGetPublicIPRequest> createGetPublicIPRequest();
	boost::shared_ptr<PlatformNATTraversalForwardPortRequest> createForwardPortRequest(unsigned int localPort, unsigned int publicPort);
	boost::shared_ptr<PlatformNATTraversalRemovePortForwardingRequest> createRemovePortForwardingRequest(unsigned int localPort, unsigned int publicPort);

	void run();
	void addRequestToQueue(PlatformNATTraversalRequest::ref);

private:
	void checkAvailableNATTraversalProtocols();
	void handleUPnPGetPublicIPResult(boost::optional<HostAddress> address);
	void handleNATPMPGetPublicIPResult(boost::optional<HostAddress> address);

private:
	BackendType backendType;
	EventLoop* eventLoop;
	bool stopRequested;
	boost::thread* thread;
	std::deque<PlatformNATTraversalRequest::ref> queue;
	boost::mutex queueMutex;
	boost::condition_variable queueNonEmpty;
};

}
